#ifndef PERF_H
#define PERF_H

#include <iostream>
#include "info.h"
#include <string>
#include <string.h>
#include <stdio.h>
#include <thread>
#include <mutex> 
#include <sstream>
#include <algorithm>

extern std::mutex mtx; 

struct perf_stats{
	public:
		long double kfree_skb;
		long double consume_skb;
};

extern struct perf_stats stats;

using namespace std;

void parse(struct info &str, std::string s1);
void getPerf(int totalTime, string procPids);
void setPerfStats(struct info_settings &statistics);
string getPidPerf(string pname);
int stringToNumber(string s);
bool is_number(const std::string& s);

#endif
