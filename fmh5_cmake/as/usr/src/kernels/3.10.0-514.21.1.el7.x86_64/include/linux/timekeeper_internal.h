/*
 * You SHOULD NOT be including this unless you're vsyscall
 * handling code or timekeeping internal code!
 */

#ifndef _LINUX_TIMEKEEPER_INTERNAL_H
#define _LINUX_TIMEKEEPER_INTERNAL_H

#include <linux/clocksource.h>
#include <linux/jiffies.h>
#include <linux/time.h>

/**
 * struct tk_read_base - base structure for timekeeping readout
 * @clock:	Current clocksource used for timekeeping.
 * @cycle_last: @clock cycle value at last update
 * @mult:	NTP adjusted multiplier for scaled math conversion
 * @shift:	Shift value for scaled math conversion
 * @xtime_nsec: Shifted (fractional) nano seconds offset for readout
 * @base_mono:  ktime_t (nanoseconds) base time for readout
 *
 * This struct has size 56 byte on 64 bit. Together with a seqcount it
 * occupies a single 64byte cache line.
 *
 * The struct is separate from struct timekeeper as it is also used
 * for a fast NMI safe accessor to clock monotonic.
 */
struct tk_read_base {
	struct clocksource	*clock;
	cycle_t			cycle_last;
	u32			mult;
	u32			shift;
	u64			xtime_nsec;
	ktime_t			base;
};

/**
 * struct timekeeper - Structure holding internal timekeeping values.
 * @tkr_mono:		The readout base structure for CLOCK_MONOTONIC
 * @tkr_raw:		The readout base structure for CLOCK_MONOTONIC_RAW
 * @xtime_sec:		Current CLOCK_REALTIME time in seconds
 * @wall_to_monotonic:	CLOCK_REALTIME to CLOCK_MONOTONIC offset
 * @offs_real:		Offset clock monotonic -> clock realtime
 * @offs_boot:		Offset clock monotonic -> clock boottime
 * @offs_tai:		Offset clock monotonic -> clock tai
 * @tai_offset:		The current UTC to TAI offset in seconds
 * @raw_time:		Monotonic raw base time in timespec64 format
 * @clock_was_set_seq:	The sequence number of clock was set events
 * @cs_was_changed_seq:	The sequence number of clocksource change events
 * @next_leap_ktime:	CLOCK_MONOTONIC time value of a pending leap-second
 * @cycle_interval:	Number of clock cycles in one NTP interval
 * @xtime_interval:	Number of clock shifted nano seconds in one NTP
 *			interval.
 * @xtime_remainder:	Shifted nano seconds left over when rounding
 *			@cycle_interval
 * @raw_interval:	Raw nano seconds accumulated per NTP interval.
 * @ntp_error:		Difference between accumulated time and NTP time in ntp
 *			shifted nano seconds.
 * @ntp_error_shift:	Shift conversion between clock shifted nano seconds and
 *			ntp shifted nano seconds.
 * @total_sleep_time:	Time spent in suspend.
 *
 * Note: For timespec(64) based interfaces wall_to_monotonic is what
 * we need to add to xtime (or xtime corrected for sub jiffie times)
 * to get to monotonic time.  Monotonic is pegged at zero at system
 * boot time, so wall_to_monotonic will be negative, however, we will
 * ALWAYS keep the tv_nsec part positive so we can use the usual
 * normalization.
 *
 * wall_to_monotonic is moved after resume from suspend for the
 * monotonic time not to jump. We need to add total_sleep_time to
 * wall_to_monotonic to get the real boot based time offset.
 *
 * wall_to_monotonic is no longer the boot time, getboottime must be
 * used instead.
 */
struct timekeeper {
	struct tk_read_base	tkr_mono;
	struct tk_read_base	tkr_raw;
	u64			xtime_sec;
	struct timespec64	wall_to_monotonic;
	ktime_t			offs_real;
	ktime_t			offs_boot;
	ktime_t			offs_tai;
	s32			tai_offset;
	struct timespec64	raw_time;

	/* The following members are for timekeeping internal use */
	unsigned int		clock_was_set_seq;
	u8			cs_was_changed_seq;
	ktime_t			next_leap_ktime;
	cycle_t			cycle_interval;
	u64			xtime_interval;
	s64			xtime_remainder;
	u32			raw_interval;
	s64			ntp_error;
	u32			ntp_error_shift;
	/* The ntp_tick_length() value currently being used.
	 * This cached copy ensures we consistently apply the tick
	 * length for an entire tick, as ntp_tick_length may change
	 * mid-tick, and we don't want to apply that new value to
	 * the tick in progress.
	 */
	u64			ntp_tick;
	u32			ntp_err_mult;

	struct timespec64	total_sleep_time;
};

static inline struct timespec64 tk_xtime(struct timekeeper *tk)
{
	struct timespec64 ts;

	ts.tv_sec = tk->xtime_sec;
	ts.tv_nsec = (long)(tk->tkr_mono.xtime_nsec >> tk->tkr_mono.shift);
	return ts;
}


#ifdef CONFIG_GENERIC_TIME_VSYSCALL

extern void update_vsyscall(struct timekeeper *tk);
extern void update_vsyscall_tz(void);

#elif defined(CONFIG_GENERIC_TIME_VSYSCALL_OLD)

extern void update_vsyscall_old(struct timespec *ts, struct timespec *wtm,
				struct clocksource *c, u32 mult);
extern void update_vsyscall_tz(void);

static inline void update_vsyscall(struct timekeeper *tk)
{
	struct timespec xt;

	xt = tk_xtime(tk);
	update_vsyscall_old(&xt, &tk->wall_to_monotonic, tk->tkr_mono.clock,
			    tk->tkr_mono.mult);
}

#else

static inline void update_vsyscall(struct timekeeper *tk)
{
}
static inline void update_vsyscall_tz(void)
{
}
#endif

#endif /* _LINUX_TIMEKEEPER_INTERNAL_H */
