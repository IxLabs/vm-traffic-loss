#include "netstat.h"

vector<long long int> getNumbers(string str){
	vector<long long int> v;
	try {
			std::regex re("[0-9]+");
			std::sregex_iterator next(str.begin(), str.end(), re);
			std::sregex_iterator end;
		  	while (next != end) {
				std::smatch match = *next;
				v.push_back(stoi(match.str()));
				next++;
		  		}
	} catch (std::regex_error& e) {
	  // Syntax error in the regular expression
	}
	return v;
}

void getNetstat(struct info_settings &statistics, struct info_settings last_stats){
	string interface;
	char buffer[512];
	string str, ip , tcp, udp;
	FILE *in;
	vector <long long int> v;
	getNetstatPackets(statistics, last_stats);
	if(!(in = fopen("/proc/net/snmp", "r"))) {
			cout<<"Eroare fopen"<<endl;
			return;
		}
	while(fgets(buffer, sizeof(buffer), in) != NULL ) {
		string str (buffer);
		string toFindIp (IpSectionStart);
		string toFindTcp (TcpSectionStart);
		string toFindUdp (UdpSectionStart);
		if (str.find(toFindIp)!= std::string::npos){
			v = getNumbers(str);
			if(v.size() == 19)
				setIpStats(statistics, last_stats, v);
		}
		if (str.find(toFindTcp)!= std::string::npos){
			v = getNumbers(str);
			if(v.size() == 15)
				setTcpStats(statistics, last_stats, v);
		}
		if (str.find(toFindUdp)!= std::string::npos){
			v = getNumbers(str);
			if(v.size() == 7)
				setUdpStats(statistics, last_stats, v);
		}
		v.clear();
	}
	fclose(in);
}

void setIpStats(struct info_settings &statistics, 
				struct info_settings last_stats, vector <long long int> v){
	statistics.protocol.ip.totalReceived = v[2]-last_stats.protocol.ip.totalReceived;
	statistics.protocol.ip.inAddrErrors = v[4]-last_stats.protocol.ip.inAddrErrors;
	statistics.protocol.ip.incomingDiscarded = v[7]-last_stats.protocol.ip.incomingDiscarded;
	statistics.protocol.ip.incomingDelivered = v[8]-last_stats.protocol.ip.incomingDelivered;
	statistics.protocol.ip.requestsSentOut = v[9]-last_stats.protocol.ip.requestsSentOut;
	statistics.protocol.ip.outgoingDropped = v[10]-last_stats.protocol.ip.outgoingDropped;
	statistics.protocol.ip.reasmTimeout = v[12]-last_stats.protocol.ip.reasmTimeout;
	statistics.protocol.ip.reasmReqds = v[13]-last_stats.protocol.ip.reasmReqds;
	statistics.protocol.ip.reasmOKs = v[14]-last_stats.protocol.ip.reasmOKs;
	statistics.protocol.ip.reasmFails = v[15]-last_stats.protocol.ip.reasmFails;
	statistics.protocol.ip.fragOKs = v[16]-last_stats.protocol.ip.fragOKs;
	statistics.protocol.ip.fragFails = v[17]-last_stats.protocol.ip.fragFails;
	statistics.protocol.ip.fragCreates = v[18]-last_stats.protocol.ip.fragCreates;
	
}

void setTcpStats(struct info_settings &statistics, 
				struct info_settings last_stats, vector <long long int> v){
	statistics.protocol.tcp.activeConnections = v[4];
	statistics.protocol.tcp.failedConnections = v[6];
	statistics.protocol.tcp.segmentsRecv = v[9]-last_stats.protocol.tcp.segmentsRecv;
	statistics.protocol.tcp.segmentsSend = v[10]-last_stats.protocol.tcp.segmentsSend;
	statistics.protocol.tcp.badSegments = v[12]-last_stats.protocol.tcp.badSegments;
	statistics.protocol.tcp.resetsSent = v[13]-last_stats.protocol.tcp.resetsSent;	
}

void setUdpStats(struct info_settings &statistics, 
				struct info_settings last_stats, vector <long long int> v){

	statistics.protocol.udp.packetsReceived = v[0]-last_stats.protocol.udp.packetsReceived;
	statistics.protocol.udp.unknownPortRecv = v[1]-last_stats.protocol.udp.unknownPortRecv;
	statistics.protocol.udp.recvErrors = v[2]-last_stats.protocol.udp.recvErrors;
	statistics.protocol.udp.packetsSent = v[3]-last_stats.protocol.udp.packetsSent;
}

void getNetstatPackets(struct info_settings &statistics, struct info_settings last_stats){
	string interface;
	char buffer[512];
	string str;
	int n;
	FILE *in;
	vector <long long int> v;
	if(!(in = popen("netstat -i", "r"))) {
			cout<<"Eroare popen"<<endl;
			return;
		}
	while(fgets(buffer, sizeof(buffer), in) != NULL ) {
		if(strstr(buffer, "lo") == NULL)
			str.append(buffer);
		//else
			//cout << buffer << endl;
	}
	try {
	  std::regex re("(\\b\\d+)");
	  std::sregex_iterator next(str.begin(), str.end(), re);
	  std::sregex_iterator end;
	  while (next != end) {
		std::smatch match = *next;
		v.push_back(stoi(match.str()));
		next++;
		setRxPackets(statistics, last_stats, v);
		setTxPackets(statistics, last_stats, v);
	  }
	} catch (std::regex_error& e) {
	  // Syntax error in the regular expression
	}
	
	pclose(in);
}

void setRxPackets(struct info_settings &statistics, struct info_settings last_stats, vector <long long int> v){
	statistics.totalRecv = 0;
	for(int i=2; i<v.size(); i+=10)
		statistics.totalRecv += v[i];
	statistics.totalRecv -=last_stats.totalRecv;
	
}
void setTxPackets(struct info_settings &statistics, struct info_settings last_stats, vector <long long int> v){
	statistics.totalSend = 0;
	for(int i=6; i<v.size(); i+=10)
		statistics.totalSend += v[i];
	statistics.totalSend -=last_stats.totalSend;
}

