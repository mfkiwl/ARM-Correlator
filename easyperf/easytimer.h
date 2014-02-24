

#ifndef __EASYTIMER_H__
#define __EASYTIMER_H__

#include <iostream>

#include "easyperf.h"


class EasyTimer
{
	public:
		EasyTimer();
		~EasyTimer();
		
		void Start(); //Start a new timer.
		void Stop(); //Stop timer and add time to total.
		void Reset();
		
		double GetTimeInSeconds();
		uint64_t GetTimeInCycles();
		uint64_t GetTotalTimeInCycles();
		uint64_t GetAverageTimeInCycles();
		uint64_t GetRunCount();
		
		double GetCPUSpeedMHz();
		
		std::ostream &Print(std::ostream &);
	
	private:
		double _CPUSpeedMHz;
		uint64_t _startTime[1];
		uint64_t _stopTime[1];
		
		uint64_t _totalTime;
		uint64_t _count;
		
		void FindCPUSpeedMHz();
		
		void PrintTime(std::ostream &, const char *which, double time) const;
};

#endif