#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <fcntl.h>

//#include <poll_thread.h>
#include <memcheck.h>
#include <poller.h>
#include <uvlog.h>

//#define FREE_CLEAR(x)	do { if((x) != 0) { free((void *)(x)); (x)=0; } } while(0)
//#define REALLOC(p,sz)	({ void *a=realloc(p,sz); if(a) p = (typeof(p))a; a; })
//#define CALLOC(x, y)	calloc(x, y)

CPollerObject::CPollerObject (CPollerUnit *o, int fd)
	:
	netfd (fd),
	ownerUnit(o),
	newEvents (0),
	oldEvents (0),
	epslot(NULL)
{
}

CPollerObject::~CPollerObject ()
{
	if (ownerUnit && epslot)
		ownerUnit->FreeEpollSlot (epslot);

	if (netfd > 0) {
		close (netfd);
		netfd = 0;
	}
}

int CPollerObject::AttachPoller (CPollerUnit *unit)
{
	if(unit) {
		if( ownerUnit==NULL)
			ownerUnit = unit;
		else
			return -1;
	}
	if(netfd < 0)
		return -1;

	if(epslot==NULL) {
		if (!(epslot = ownerUnit->AllocEpollSlot ()))
			return -1;
		epslot->poller = this;

		int flag = fcntl (netfd, F_GETFL);
		fcntl (netfd, F_SETFL, O_NONBLOCK | flag);
		struct epoll_event ev;
		ev.events = newEvents;
		ev.data.u64 = (++epslot->seq);
		ev.data.u64 = (ev.data.u64 << 32) + ownerUnit->GetSlotId (epslot);
		if (ownerUnit->Epctl (EPOLL_CTL_ADD, netfd, &ev) == 0)
			oldEvents = newEvents;
		else {
			LOG_WARNING("Epctl: %m");
			return -1;
		}
		
		LOG_DEBUG("Attach poller succ:%d",netfd);
		return 0;

	}
	
	LOG_DEBUG("Attach poller succ:%d",netfd);
	
	return ApplyEvents ();
}

int CPollerObject::DetachPoller() {
	if(epslot) {
		struct epoll_event ev;
		if (ownerUnit->Epctl (EPOLL_CTL_DEL, netfd, &ev) == 0)
			oldEvents = newEvents;
		else {
			LOG_WARNING("Epctl: %m");
			return -1;
		}
		ownerUnit->FreeEpollSlot(epslot);
		epslot = NULL;
	}
	return 0;
}

int CPollerObject::ApplyEvents ()
{
	if (epslot==NULL || oldEvents == newEvents)
		return 0;

	struct epoll_event ev;

	ev.events = newEvents;
	ev.data.u64 = (++epslot->seq);
	ev.data.u64 = (ev.data.u64 << 32) + ownerUnit->GetSlotId (epslot);
	if (ownerUnit->Epctl (EPOLL_CTL_MOD, netfd, &ev) == 0)
		oldEvents = newEvents;
	else {
		LOG_WARNING("Epctl: %m");
		return -1;
	}

	return 0;
}

void CPollerObject::InitPollFd(struct pollfd *pfd)
{
	pfd->fd = netfd;
	pfd->events = newEvents;
	pfd->revents = 0;
}

void CPollerObject::InputNotify(void) {
	EnableInput(false);
}

void CPollerObject::OutputNotify(void) {
	EnableOutput(false);
}

void CPollerObject::HangupNotify(void) {
	delete this;
}

CPollerUnit::CPollerUnit(int mp)
{
	maxPollers = mp;
	epfd = -1;
	ep_events = NULL;
	pollerTable = NULL;
	freeSlotList = NULL;
	usedPollers = 0;
}

CPollerUnit::~CPollerUnit() {
	for (int i = 0; i < maxPollers; i++) 
	{
		if (pollerTable[i].freeList)
			continue;
		//delete pollerTable[i].poller;
	}

	FREE_CLEAR(pollerTable);

	if (epfd != -1)
	{
		close (epfd);
		epfd = -1;
	}

	FREE_CLEAR(ep_events);
}

int CPollerUnit::SetMaxPollers(int mp)
{
	if(epfd >= 0)
		return -1;
	maxPollers = mp;
	return 0;
}

int CPollerUnit::InitializePollerUnit(void)
{
	pollerTable = (struct CEpollSlot *)CALLOC(maxPollers, sizeof (*pollerTable));

	if (!pollerTable)
	{
		LOG_ERROR("calloc failed, num=%d, %m", maxPollers);
		return -1;
	}

	for (int i = 0; i < maxPollers - 1; i++)
	{
		pollerTable[i].freeList = &pollerTable[i+1];
	}

	pollerTable[maxPollers - 1].freeList = NULL;
	freeSlotList = &pollerTable[0];

	ep_events = (struct epoll_event *)CALLOC(maxPollers, sizeof (struct epoll_event));

	if (!ep_events)
	{
		LOG_ERROR("malloc failed, %m");
		return -1;
	}

	if ((epfd = epoll_create (maxPollers)) == -1)
	{
		LOG_WARNING("epoll_create failed, %m");
		return -1;
	}
	fcntl(epfd, F_SETFD, FD_CLOEXEC);
	return 0;
}

inline int CPollerUnit::VerifyEvents (struct epoll_event *ev)
{
	int idx = EPOLL_DATA_SLOT (ev);

	if ((idx >= maxPollers) || (EPOLL_DATA_SEQ (ev) != pollerTable[idx].seq))
	{
		return -1;
	}
	if(pollerTable[idx].poller == NULL || pollerTable[idx].freeList != NULL)
	{
		LOG_NOTICE("receive invalid epoll event. idx=%d seq=%d poller=%p freelist=%p event=%x",
				idx, (int)EPOLL_DATA_SEQ(ev), pollerTable[idx].poller, 
				pollerTable[idx].freeList, ev->events);
		return -1;
	}
	return 0;
}

void CPollerUnit::FreeEpollSlot (CEpollSlot *p)
{
	p->freeList = freeSlotList;
	freeSlotList = p;
	usedPollers--;
	p->seq++;
	p->poller = NULL;
}

struct CEpollSlot *CPollerUnit::AllocEpollSlot ()
{
	CEpollSlot *p = freeSlotList;

	if (0 == p) 
	{
		LOG_WARNING("no free epoll slot, usedPollers=%d", usedPollers);
		return NULL;
	}
	
	usedPollers++;
	freeSlotList = freeSlotList->freeList;
	p->freeList = NULL;

	return p;
}

int CPollerUnit::Epctl (int op, int fd, struct epoll_event *events)
{
	if (epoll_ctl (epfd,  op, fd, events) == -1)
    {
		LOG_WARNING("epoll_ctl error, epfd=%d, fd=%d", epfd, fd);

		return -1;
	}

	return 0;
}

void CPollerUnit::WaitPollerEvents(int timeout) {
	nrEvents = epoll_wait (epfd, ep_events, maxPollers, timeout);
}

void CPollerUnit::ProcessPollerEvents(void) {
	for (int i = 0; i < nrEvents; i++)
	{
		if(VerifyEvents (ep_events+i) == -1)
		{
			LOG_NOTICE("VerifyEvents failed, ep_events[%d].data.u64 = %llu", i, (unsigned long long)ep_events[i].data.u64);
			continue;
		}

		CEpollSlot *s = &pollerTable[EPOLL_DATA_SLOT(ep_events+i)];
		CPollerObject *p = s->poller;

		p->newEvents = p->oldEvents;
		if(ep_events[i].events & (EPOLLHUP | EPOLLERR))
		{
			p->HangupNotify();
			continue;
		}

		if(ep_events[i].events & EPOLLIN)
			p->InputNotify();

		if(s->poller==p && ep_events[i].events & EPOLLOUT)
			p->OutputNotify();

		if(s->poller==p)
			p->ApplyEvents();
	}
}

