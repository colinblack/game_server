/*
 * TimerThread.cpp
 *
 *  Created on: 2018年11月1日
 *      Author: Administrator
 */

#include "TimerThread.h"
#include "Kernel.h"

CTimerThread::CTimerThread(const char *addr, short port, long usec, long sec) {
	memcpy(m_addr, addr, sizeof(m_addr));
	m_port = port;
	m_usec = usec;
	m_sec = sec;
	m_fd = -1;
}

CTimerThread::~CTimerThread() {
}

void CTimerThread::Run() {
	struct sockaddr_in inaddr;
	bzero(&inaddr, sizeof(struct sockaddr_in));
	inaddr.sin_family = AF_INET;
	inaddr.sin_port = htons(m_port);
	if (inet_pton(AF_INET, m_addr, &inaddr.sin_addr) <= 0) {
		error_log("addr error addr=%s port=%d", m_addr, m_port);
		return;
	}
	if ((m_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		error_log("fd error addr=%s port=%d err=%m", m_addr, m_port);
		return;
	}
	if (connect(m_fd, (struct sockaddr *) &inaddr, sizeof(struct sockaddr)) != 0) {
		error_log("connect error addr=%s port=%d err=%m", m_addr, m_port);
		return;
	}

	struct timeval timeOut;
	CNetPacket packet;
	packet.head = MAGIC_HEADER;
	packet.ptype = PROTOCOL_TYPE_SECOND_TIMER;
	CStaticBuffer<PACKET_HEADER_SIZE + 8> buf;
	CStaticBuffer<8> body;

	while (IsRun()) {
		timeOut.tv_sec = m_sec;
		timeOut.tv_usec = m_usec;
		if (select(0, NULL, NULL, NULL, &timeOut) == 0 && IsRun()) {
			uint64_t utime = GET_USEC();
			body.Clear();
			body.Append(reinterpret_cast<byte*>(&utime), sizeof(utime));
			packet.SetBody(&body);
			packet.Encode(&buf);
			if (send(m_fd, reinterpret_cast<char*>(buf.GetNativeBuffer()), buf.GetSize(), 0) <= 0) {
				error_log("fatal:send timer packet failed,%m");
			}
		}
	}
}
