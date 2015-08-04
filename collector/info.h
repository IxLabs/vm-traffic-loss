#ifndef INFO_H
#define INFO_H

#include <stdio.h>
#include <string>
#include "iostream"

#define TestNumber 0

using namespace std;

struct proto_errors
{
	public:
		int checkSum;
};

struct sockets_details
{
	public:
		int established;
		int listening;
		int connected;
};

struct resourcesUsed
{
	public:
		double memUsed;;
		double maxMemUsed;
		int timeMemThreshold;
		double cpuUsed;
		double maxCpuAvg;
		int timeCpuThreshold;
		int interrupts;
};
/*
    Total Packets Received
    	Number of total IP datagrams received

    Bad Header Checksum or Fragments Dropped

	Fragments Received
    	Number of total fragments received.
    
	Dropped after Timeout

	Packets Sent from this Host

    Fragments Created
		Number of fragments created in this system when IP datagrams were sent out.



– the remaining rows below signify issues and should be low in count –
 outgoing packets dropped
 fragments dropped after timeout
 reassemblies required
 packets reassembled ok
 packet reassembles failed
 fragments failed

*/
struct ip_prot
{
	public:
		long long int totalReceived;
		int inAddrErrors;
		long long int incomingDiscarded;
		long long int incomingDelivered;
		long long int requestsSentOut;
		long long int outgoingDropped;
		int reasmTimeout;
		int reasmReqds;
		int reasmOKs;
		int reasmFails;
		int fragOKs;
		int fragFails;
		int fragCreates;
};

/*
 active connections openings <-- proactive connections opened as a client
 passive connection openings <-- connections recvd as a server
segments retransmited <-- should be a small percentage of total segments sent out.
						 A high number represents hardware or network issues
bad segments received <--"---"

*/

struct tcp_prot
{
	public:
		int activeConnections;
		int failedConnections;
		long long int segmentsRecv;
		long long int segmentsSend;
		long long int segmentsRetransmited;
		int badSegments;
		int resetsSent;
};

struct udp_prot
{
	public:
		long long int packetsReceived;
		int unknownPortRecv;
		int recvErrors;
		long long int packetsSent;
};

struct prot_details
{
	public:
		struct ip_prot ip;
		struct tcp_prot tcp;
		struct udp_prot udp;
		struct proto_errors error;	
};

struct trace_details{
	public:
		long double kfree_skb;
		long double consume_skb;
};

struct info_settings
{
	std::string vm;
	int metric;
	long long int totalSend;
	long long int totalRecv;
	struct prot_details protocol;
	struct resourcesUsed resources;
	struct sockets_details socket;
	struct trace_details tracepoints;
	void load(const std::string &filename);
	void save(const std::string &filename);
};

void initialize(info_settings& statistics, int type);

#endif
