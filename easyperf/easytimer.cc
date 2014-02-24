
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iomanip>

#include "easytimer.h"

using namespace std;

EasyTimer::EasyTimer()
{
	FindCPUSpeedMHz();
	
	perf_init(1, EV_CYCLES);
}

void EasyTimer::FindCPUSpeedMHz()
{
#if defined __linux__
    ifstream infile("/proc/cpuinfo");
    char     buffer[256], *colon;

    while (infile.good()) {
	infile.getline(buffer, 256);

	if (strncmp("cpu MHz", buffer, 7) == 0 && (colon = strchr(buffer, ':')) != 0)
	    _CPUSpeedMHz = atof(colon + 2);
    }
#endif

    _CPUSpeedMHz = 0.0;
}

void EasyTimer::Start()
{
	perf_read_all(_startTime);
}

void EasyTimer::Stop()
{
	perf_read_all(_stopTime);
	
	_totalTime += GetTimeInCycles();
	_count++;
}

void EasyTimer::Reset()
{
	_startTime[0] = 0;
	_stopTime[0] = 0;
}

uint64_t EasyTimer::GetTimeInCycles()
{
	return _stopTime[0] - _startTime[0];
}

uint64_t EasyTimer::GetTotalTimeInCycles()
{
	return _totalTime;
}

uint64_t EasyTimer::GetAverageTimeInCycles()
{
	return _totalTime / _count;
}

uint64_t EasyTimer::GetRunCount()
{
	return _count;
}

// Gets the last timer time in seconds.
double EasyTimer::GetTimeInSeconds()
{
	double total = static_cast<double>(GetTimeInCycles());
    double res = (total / 1000000.0) / _CPUSpeedMHz;
    return res;
}


void EasyTimer::PrintTime(ostream &str, const char *which, double time) const
{
    static const char *units[] = { " ns", " us", " ms", "  s", " ks", 0 };
    const char	      **unit   = units;

    time = 1000.0 * time / _CPUSpeedMHz;

    while (time >= 999.5 && unit[1] != 0) {
	time /= 1000.0;
	++ unit;
    }

    str << which << " = " << setprecision(3) << setw(4) << time << *unit;
}


ostream &EasyTimer::Print(ostream &str)
{
    if (_CPUSpeedMHz == 0)
	str << "Could not determine CPU speed!\n";
    else if (_count > 0) {
	double total = static_cast<double>(GetTimeInCycles());
	double avg = static_cast<double>(GetAverageTimeInCycles());

	PrintTime(str, "Average:", avg);
	PrintTime(str, ", Total:", total);
	str << ", Count = " << setw(9) << _count << '\n';
    }
    else
	str << "not used\n";

    return str;
}


ostream &operator << (ostream &str, class EasyTimer &timer)
{
    return timer.Print(str);
}