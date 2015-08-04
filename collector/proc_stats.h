#ifndef PROC_STATS_H
#define PROC_STATS_H

#include "iostream"
#include <string.h>
#include "info.h"

#define cpuThreshold 0.5
#define memThreshold 80

using namespace std;

extern long double firstSample[4];
extern long double secondSample[4];
extern int cpuSamples;
extern long double cpuAvgSum;
extern long double maxCpuAvg;
extern int timeCpuThreshold;

extern int memSamples;
extern double memAvgSum;
extern double maxMemUsed;
extern int timeMemThreshold;
extern long double loadavg;

long double getInstantCpuAverage(bool &updateSwitch);
void updateCpuAverage(struct info_settings &statistics, bool &updateSwitch);
void resetCpuStats();

double getMemUsed();
void updateMemUsed(struct info_settings &statistics);
void resetMemStats();

#endif
