#include "ifconfig.h"

/*functii parsare string pentru informatii*/
int getStat(string line, string infMargin, string supMargin){
	int first = line.find(infMargin)+8;
	int second = line.find(supMargin);
	
	int len = second - first-1;
	return atoi(line.substr(first, len).c_str());
}

void parse_line(struct info_settings &statistics, string line, int mode) {
	int number;
	switch(mode){
		case 0:
				statistics.pdropped += getStat(line, "dropped:", "overruns:");
				statistics.reason = "ifconfig";
				break;
		
		case 1:
				statistics.reason = "ifconfig";
				statistics.pdropped += getStat(line, "dropped:", "overruns:");
				break;
	}
}

void parseInfo_ifconfig(struct info_settings &statistics, string interface){
	int foundRx = interface.find(ifconfigRxInf);
	int foundTx = interface.find(ifconfigTxInf, foundRx);
	int foundCollisions = interface.find(ifconfigTxSup, foundTx);
	if (foundRx != string::npos) {
		parse_line(statistics, interface.substr(foundRx, foundTx-foundRx), 0);
		parse_line(statistics, interface.substr(foundTx, foundCollisions-foundTx), 1);
	}
}


void getIfConfig(struct info_settings &statistics, bool &firstTime, 
				struct info_settings &last_stats){
	string interface;
	char buffer[512];
	FILE *in;
	if(!(in = popen("ifconfig", "r"))) {
			cout<<"Eroare popen"<<endl;
			return;
		}
	while(fgets(buffer, sizeof(buffer), in) != NULL ) {
		if(strcmp(buffer, "\n") != 0) {
			interface.append(buffer);
		}
		else{
			parseInfo_ifconfig(statistics, interface);
			interface = "";
		}
	}
	if(!firstTime){
		statistics.pdropped -= last_stats.pdropped;
	}
	else{
		firstTime = false;
	}
	pclose(in);
}

