#include <asm-generic/qrwlock_types.h>
#ifndef __LINUX_QRWLOCK_TYPES_H
#define __LINUX_QRWLOCK_TYPES_H

/*
 * include/linux/qrwlock_types.h - generic qrwlock type definitions
 *				  and initializers
 *
 * portions Copyright 2005, Red Hat, Inc., Ingo Molnar
 * Released under the General Public License (GPL).
 */
typedef struct {
	arch_qrwlock_t raw_lock;
#ifdef CONFIG_GENERIC_LOCKBREAK
	unsigned int break_lock;
#endif
#ifdef CONFIG_DEBUG_SPINLOCK
	unsigned int magic, owner_cpu;
	void *owner;
#endif
#ifdef CONFIG_DEBUG_LOCK_ALLOC
	struct lockdep_map dep_map;
#endif
} qrwlock_t;

#define QRWLOCK_MAGIC		0xdeaf1eed

#ifdef CONFIG_DEBUG_LOCK_ALLOC
# define RW_DEP_MAP_INIT(lockname)	.dep_map = { .name = #lockname }
#else
# define RW_DEP_MAP_INIT(lockname)
#endif

#ifdef CONFIG_DEBUG_SPINLOCK
#define __QRW_LOCK_UNLOCKED(lockname)					\
	(qrwlock_t)	{	.raw_lock = __ARCH_QRW_LOCK_UNLOCKED,	\
				.magic = QRWLOCK_MAGIC,			\
				.owner = SPINLOCK_OWNER_INIT,		\
				.owner_cpu = -1,			\
				RW_DEP_MAP_INIT(lockname) }
#else
#define __QRW_LOCK_UNLOCKED(lockname) \
	(qrwlock_t)	{	.raw_lock = __ARCH_QRW_LOCK_UNLOCKED,	\
				RW_DEP_MAP_INIT(lockname) }
#endif

#define DEFINE_QRWLOCK(x)	qrwlock_t x = __QRW_LOCK_UNLOCKED(x)

#endif /* __LINUX_QRWLOCK_TYPES_H */
