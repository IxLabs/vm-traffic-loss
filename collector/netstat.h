#ifndef NETSTAT_H
#define NETSTAT_H

#include <iostream>
#include "info.h"
#include <string>
#include <sstream>
#include <regex>
#include <iterator>

#define IpSectionStart "Ip:"
#define TcpSectionStart "Tcp:"
#define UdpSectionStart "Udp:"

using namespace std;

void getNetstat(struct info_settings &statistics, struct info_settings last_stats);
void setIpStats(struct info_settings &statistics, struct info_settings last_stats, vector <long long int> v);
void setTcpStats(struct info_settings &statistics, struct info_settings last_stats, vector <long long int> v);
void setRxPackets(struct info_settings &statistics, struct info_settings last_stats, vector <long long int> v);
void setTxPackets(struct info_settings &statistics, struct info_settings last_stats, vector <long long int> v);
void setUdpStats(struct info_settings &statistics, struct info_settings last_stats, vector <long long int> v);
void getNetstatPackets(struct info_settings &statistics, struct info_settings last_stats);
vector<long long int> getNumbers(string str);
#endif
