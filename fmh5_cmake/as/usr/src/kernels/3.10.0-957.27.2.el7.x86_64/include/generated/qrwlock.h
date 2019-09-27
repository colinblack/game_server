#include <asm/qrwlock.h>
#ifndef __LINUX_QRWLOCK_H
#define __LINUX_QRWLOCK_H


/*
 * qrwlock related methods
 *
 * split out from spinlock.h
 *
 * portions Copyright 2005, Red Hat, Inc., Ingo Molnar
 * Released under the General Public License (GPL).
 */

#ifdef CONFIG_DEBUG_SPINLOCK
  extern void __qrwlock_init(qrwlock_t *lock, const char *name,
			    struct lock_class_key *key);
# define qrwlock_init(lock)					\
do {								\
	static struct lock_class_key __key;			\
								\
	__qrwlock_init((lock), #lock, &__key);			\
} while (0)
#else
# define qrwlock_init(lock)					\
	do { *(lock) = __QRW_LOCK_UNLOCKED(lock); } while (0)
#endif

#ifdef CONFIG_DEBUG_SPINLOCK
 extern void do_raw_qread_lock(qrwlock_t *lock) __acquires(lock);
#define do_raw_qread_lock_flags(lock, flags) do_raw_qread_lock(lock)
 extern int do_raw_qread_trylock(qrwlock_t *lock);
 extern void do_raw_qread_unlock(qrwlock_t *lock) __releases(lock);
 extern void do_raw_qwrite_lock(qrwlock_t *lock) __acquires(lock);
#define do_raw_qwrite_lock_flags(lock, flags) do_raw_qwrite_lock(lock)
 extern int do_raw_qwrite_trylock(qrwlock_t *lock);
 extern void do_raw_qwrite_unlock(qrwlock_t *lock) __releases(lock);
#else
# define do_raw_qread_lock(qrwlock)	do {__acquire(lock); arch_qread_lock(&(qrwlock)->raw_lock); } while (0)
# define do_raw_qread_lock_flags(lock, flags) \
		do {__acquire(lock); arch_qread_lock_flags(&(lock)->raw_lock, *(flags)); } while (0)
# define do_raw_qread_trylock(qrwlock)	arch_qread_trylock(&(qrwlock)->raw_lock)
# define do_raw_qread_unlock(qrwlock)	do {arch_qread_unlock(&(qrwlock)->raw_lock); __release(lock); } while (0)
# define do_raw_qwrite_lock(qrwlock)	do {__acquire(lock); arch_qwrite_lock(&(qrwlock)->raw_lock); } while (0)
# define do_raw_qwrite_lock_flags(lock, flags) \
		do {__acquire(lock); arch_qwrite_lock_flags(&(lock)->raw_lock, *(flags)); } while (0)
# define do_raw_qwrite_trylock(qrwlock)	arch_qwrite_trylock(&(qrwlock)->raw_lock)
# define do_raw_qwrite_unlock(qrwlock)	do {arch_qwrite_unlock(&(qrwlock)->raw_lock); __release(lock); } while (0)
#endif

#define qread_can_lock(qrwlock)		arch_qread_can_lock(&(qrwlock)->raw_lock)
#define qwrite_can_lock(qrwlock)		arch_qwrite_can_lock(&(qrwlock)->raw_lock)

/*
 * Define the various rw_lock methods.  Note we define these
 * regardless of whether CONFIG_SMP or CONFIG_PREEMPT are set. The various
 * methods are defined as nops in the case they are not required.
 */
#define qread_trylock(lock)	__cond_lock(lock, _raw_qread_trylock(lock))
#define qwrite_trylock(lock)	__cond_lock(lock, _raw_qwrite_trylock(lock))

#define qwrite_lock(lock)	_raw_qwrite_lock(lock)
#define qread_lock(lock)		_raw_qread_lock(lock)

#if defined(CONFIG_SMP) || defined(CONFIG_DEBUG_SPINLOCK)

#define qread_lock_irqsave(lock, flags)			\
	do {						\
		typecheck(unsigned long, flags);	\
		flags = _raw_qread_lock_irqsave(lock);	\
	} while (0)
#define qwrite_lock_irqsave(lock, flags)			\
	do {						\
		typecheck(unsigned long, flags);	\
		flags = _raw_qwrite_lock_irqsave(lock);	\
	} while (0)

#else

#define qread_lock_irqsave(lock, flags)			\
	do {						\
		typecheck(unsigned long, flags);	\
		_raw_qread_lock_irqsave(lock, flags);	\
	} while (0)
#define qwrite_lock_irqsave(lock, flags)			\
	do {						\
		typecheck(unsigned long, flags);	\
		_raw_qwrite_lock_irqsave(lock, flags);	\
	} while (0)

#endif

#define qread_lock_irq(lock)		_raw_qread_lock_irq(lock)
#define qread_lock_bh(lock)		_raw_qread_lock_bh(lock)
#define qwrite_lock_irq(lock)		_raw_qwrite_lock_irq(lock)
#define qwrite_lock_bh(lock)		_raw_qwrite_lock_bh(lock)
#define qread_unlock(lock)		_raw_qread_unlock(lock)
#define qwrite_unlock(lock)		_raw_qwrite_unlock(lock)
#define qread_unlock_irq(lock)		_raw_qread_unlock_irq(lock)
#define qwrite_unlock_irq(lock)		_raw_qwrite_unlock_irq(lock)

#define qread_unlock_irqrestore(lock, flags)			\
	do {							\
		typecheck(unsigned long, flags);		\
		_raw_qread_unlock_irqrestore(lock, flags);	\
	} while (0)
#define qread_unlock_bh(lock)		_raw_qread_unlock_bh(lock)

#define qwrite_unlock_irqrestore(lock, flags)		\
	do {						\
		typecheck(unsigned long, flags);	\
		_raw_qwrite_unlock_irqrestore(lock, flags);	\
	} while (0)
#define qwrite_unlock_bh(lock)		_raw_qwrite_unlock_bh(lock)

#define qwrite_trylock_irqsave(lock, flags) \
({ \
	local_irq_save(flags); \
	qwrite_trylock(lock) ? \
	1 : ({ local_irq_restore(flags); 0; }); \
})

#endif /* __LINUX_QRWLOCK_H */
