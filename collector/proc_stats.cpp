#include "proc_stats.h"

long double firstSample[4];
long double secondSample[4];
int cpuSamples;
long double cpuAvgSum;
long double maxCpuAvg;
int timeCpuThreshold;

int memSamples;
double memAvgSum;
double maxMemUsed;
int timeMemThreshold;	
long double loadavg;

long double getInstantCpuAverage(bool &updateSwitch){
    FILE *fp;
	if(updateSwitch){
		fp = fopen("/proc/stat","r");
		fscanf(fp,"%*s %Lf %Lf %Lf %Lf",&firstSample[0],&firstSample[1],&firstSample[2],&firstSample[3]);
		fclose(fp);
	}
	else{
    	fp = fopen("/proc/stat","r");
    	fscanf(fp,"%*s %Lf %Lf %Lf %Lf",&secondSample[0],&secondSample[1],&secondSample[2],&secondSample[3]);
    	fclose(fp);
		loadavg = ((secondSample[0]+secondSample[1]+secondSample[2]) - 
				(firstSample[0]+firstSample[1]+firstSample[2])) / 
				((secondSample[0]+secondSample[1]+secondSample[2]+secondSample[3]) - 
				(firstSample[0]+firstSample[1]+firstSample[2]+firstSample[3]));
	}
    
	return loadavg;
}

void updateCpuAverage(struct info_settings &statistics, bool &updateSwitch){
	long double loadAverage = getInstantCpuAverage(updateSwitch);
	if( maxCpuAvg < loadAverage){
		maxCpuAvg = loadAverage;
	}
	if(loadAverage > cpuThreshold){
		timeCpuThreshold++;
	}
	if( !updateSwitch){
		cpuSamples++;
		cpuAvgSum += loadAverage;
		statistics.resources.cpuUsed = cpuAvgSum / cpuSamples * 100;
		statistics.resources.maxCpuAvg = maxCpuAvg * 100;
		statistics.resources.timeCpuThreshold = timeCpuThreshold;
    }
	updateSwitch = !updateSwitch;
}

double getMemUsed(){
	long double totalMem, freeMem, usedMem;
    FILE *fp;
    fp = fopen("/proc/meminfo","r");
    fscanf(fp,"%*s %Lf %*s %*s %Lf",&totalMem, &freeMem);
    fclose(fp);

	usedMem = totalMem - freeMem;
	return usedMem/totalMem*100;
}

void updateMemUsed(struct info_settings &statistics){
	double usedMem = getMemUsed();
	
	if( maxMemUsed < usedMem){
		maxMemUsed = usedMem;
	}
	if(usedMem > memThreshold){
		timeMemThreshold++;
	}
	memAvgSum += usedMem;
	memSamples++;
	statistics.resources.memUsed = memAvgSum / memSamples;
	statistics.resources.maxMemUsed = maxMemUsed;
	statistics.resources.timeMemThreshold = timeMemThreshold;
}

void resetCpuStats(){
	cpuSamples = 0;
	cpuAvgSum = 0;
	maxCpuAvg = 0;
	timeCpuThreshold = 0;
}

void resetMemStats(){
	memSamples = 0;
	memAvgSum = 0;
	maxMemUsed = 0;
	timeMemThreshold = 0;
}
	
