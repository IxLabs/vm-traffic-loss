#ifndef IFCONFIG_H
#define IFCONFIG_H

#include "iostream"
#include <stdio.h>
#include <string.h>
#include "info.h"

using namespace std;

#define ifconfigRxInf	"RX packets:"
#define ifconfigTxInf	"TX packets:"
#define ifconfigTxSup	"carrier"

int getStat(string line, string infMargin, string supMargin);

void parse_line(struct info_settings &statistics, string line, int mode);

void parseInfo_ifconfig(struct info_settings &statistics, string interface);

void getIfConfig(struct info_settings &statistics, bool &firstTime, 
				struct info_settings &last_stats);
#endif
