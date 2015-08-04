#include "iostream"
#include "ifconfig.h"
#include "proc_stats.h"
#include "netstat.h"
#include "socket_stats.h"
#include "perf.h"
#include <thread>
#include <stdio.h>
#include <string>
#include <thread>
#include <chrono> 
#include <set>
#include <exception>
#include <stdlib.h>

using namespace std;

/*
argument 1: collector's samples frequency
argument 2: total running time
argument 3: process name to monitor with perf
argument 4: vm name/address
argument 5: destination for sending results/AgentServer
argument 6: metric used for test
*/

int main(int argc,char **argv ) {
	struct info_settings statistics;
	struct info_settings first_stats;
	struct info_settings stats;
	bool firstTime = true;
	bool updateSwitch = true;
	if(argc < 7 ){
		cout << "Not enough arguments!"<<endl;
		return -1;
	}
	int frequency = atoi(argv[1]);
	int totalTime = atoi(argv[2]);
	string pname (argv[3]);
	string destination (argv[5]);
	int runningTime = 0;
	string procPids = getPidPerf(pname);
	initialize(statistics, 1);
	initialize(first_stats, 1);
	initialize(stats, 1);
	getNetstat(first_stats, statistics);
	getSocketInfo(first_stats, stats);
	//cout << "ajunge aici!"<<endl;
	try
		{
			first_stats.save("first_stats.xml");
		}
		catch (std::exception &e)
		{
			cout << "Error: " << e.what() << "\n";
		}
	
	if(procPids.compare("") == 0){
		cout << "No processes found for perf to inspect, will use -a parameter!"<<endl;
		procPids.append("-a");
	}
	resetCpuStats();
	resetMemStats();
	thread perfThread(getPerf, totalTime, procPids);
	while(runningTime < totalTime){
		initialize(statistics, 0);
		updateCpuAverage(statistics, updateSwitch);
		updateMemUsed(statistics);
		getNetstat(statistics, first_stats);
		getSocketInfo(statistics, first_stats);
		setPerfStats(statistics);
		/*try
		{
			statistics.save("info_settings_out.xml");
		}
		catch (std::exception &e)
		{
			cout << "Error: " << e.what() << "\n";
		}*/
		this_thread::sleep_for (std::chrono::seconds(frequency));
		runningTime += frequency;
	}
	cout << "Main finished!"<<endl;
	perfThread.join();	
	//save only one time
	setPerfStats(statistics);
	statistics.vm = argv[4];
	statistics.metric = atoi(argv[6]);
	//cout << statistics.bandwidth << endl;
	try
	{
		statistics.save("info_settings_out.xml");
	}
	catch (std::exception &e)
	{
		cout << "Error: " << e.what() << "\n";
	}
	//maybe send data
	string sendCommand = "./sendFileClient.sh "+destination;
	int ret = system(sendCommand.c_str());
	if(ret == -1)
		cout << "Not executed send file!"<<endl;
}
