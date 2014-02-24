/*
Modified by: Mitchell Cox (uberflyx) (mitch@enox.co.za)
Date: 21 February 2014
Changelog:
> Added support for ARM
*/

#ifndef __EASYPERF_H__
#define __EASYPERF_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <linux/perf_event.h> //perhaps shouldn't include this - but we need to know the events

// Extra options for each event
#define PERFMON_EVENTSEL_OS     (1 << 17)
#define PERFMON_EVENTSEL_USR    (1 << 16)

int perf_init(unsigned int num_ctrs, ...);
void perf_close();

uint64_t perf_read(unsigned int ctr);
void perf_read_all(uint64_t* vals);

//See http://man7.org/linux/man-pages/man2/perf_event_open.2.html for information.

#define EV_CYCLES          		PERF_COUNT_HW_CPU_CYCLES
#define EV_REF_CYCLES      		PERF_COUNT_HW_REF_CPU_CYCLES
#define EV_INSTRUCTIONS         PERF_COUNT_HW_INSTRUCTIONS
#define EV_BRANCH_INSTRUCTIONS  PERF_COUNT_HW_BRANCH_INSTRUCTIONS
#define EV_BRANCH_MISS     		PERF_COUNT_HW_BRANCH_MISSES
#define EV_CACHE_MISS			PERF_COUNT_HW_CACHE_MISSES
#define EV_CACHE_REF			PERF_COUNT_HW_CACHE_REFERENCES //use with csche miss to calculate rate

#if (defined __i386 || defined __x86_64)

// microarch specific
#define I7_L3_REFS      (0x2e | (0x4f << 8))
#define I7_L3_MISS      (0x2e | (0x41 << 8))

#define I7_L2_REFS      (0x24 | (0xff << 8))
#define I7_L2_MISS      (0x24 | (0xaa << 8))

#define I7_ICACHE_HITS  (0x80 | (0x01 << 8))
#define I7_ICACHE_MISS  (0x80 | (0x02 << 8))

#define I7_DL1_REFS     (0x43 | (0x01 << 8))

#define I7_LOADS        (0x0b | (0x01 << 8))
#define I7_STORES       (0x0b | (0x02 << 8))

#define I7_L2_DTLB_MISS (0x49 | (0x01 << 8))
#define I7_L2_ITLB_MISS (0x85 | (0x01 << 8))

#define I7_IO_TXNS      (0x6c | (0x01 << 8))
#define I7_DRAM_REFS    (0x0f | (0x20 << 8))

#endif

#ifdef __cplusplus
}
#endif

#endif // __EASYPERF_H__