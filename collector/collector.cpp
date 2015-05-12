#include "iostream"
#include "ifconfig.h"
#include <stdio.h>
#include <string>
#include <thread>
#include <chrono> 
#include <set>
#include <exception>

using namespace std;

void initialize(info_settings& statistics){
	statistics.pdropped = 0;
}

int main(int argc,char **argv ) {
	struct info_settings statistics;
	struct info_settings last_stats;
	bool firstTime = true;
	int delay = atoi(argv[1]);
	initialize(statistics);
	initialize(last_stats);

	while(true){
		getIfConfig(statistics, firstTime, last_stats);
		try
		{	
			if(statistics.pdropped != 0){
				statistics.save("info_settings_out.xml");
				last_stats.pdropped += statistics.pdropped;
			}
		}
		catch (std::exception &e)
		{
			cout << "Error: " << e.what() << "\n";
		}
		initialize(statistics);
		this_thread::sleep_for (std::chrono::seconds(delay));
	}	
}
