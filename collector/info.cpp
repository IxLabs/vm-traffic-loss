#include "info.h"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

/*functii pentru salvare structuri info*/
void info_settings::load(const std::string &filename)
{
	std::cout << "Not Implemented yet!";

}

void initialize(info_settings& statistics, int type){
	statistics.totalSend = TestNumber;
	statistics.totalRecv = TestNumber;

	statistics.protocol.error.checkSum = TestNumber;

	statistics.protocol.ip.totalReceived = TestNumber;
	statistics.protocol.ip.incomingDiscarded = TestNumber;
	statistics.protocol.ip.incomingDelivered = TestNumber;
	statistics.protocol.ip.requestsSentOut = TestNumber;
	statistics.protocol.ip.outgoingDropped = TestNumber;
	statistics.protocol.ip.inAddrErrors = TestNumber;
	statistics.protocol.ip.reasmTimeout = TestNumber;
	statistics.protocol.ip.reasmReqds = TestNumber;
	statistics.protocol.ip.reasmOKs = TestNumber;
	statistics.protocol.ip.reasmFails = TestNumber;
	statistics.protocol.ip.fragOKs = TestNumber;
	statistics.protocol.ip.fragFails = TestNumber;
	statistics.protocol.ip.fragCreates = TestNumber;	


	statistics.protocol.udp.packetsReceived = TestNumber;
	statistics.protocol.udp.unknownPortRecv = TestNumber;
	statistics.protocol.udp.recvErrors = TestNumber;
	statistics.protocol.udp.packetsSent = TestNumber;

	statistics.protocol.tcp.activeConnections = TestNumber;
	statistics.protocol.tcp.failedConnections = TestNumber;
	statistics.protocol.tcp.segmentsRecv = TestNumber;
	statistics.protocol.tcp.segmentsSend = TestNumber;
	statistics.protocol.tcp.badSegments = TestNumber;
	statistics.protocol.tcp.resetsSent = TestNumber;	

	statistics.resources.memUsed = TestNumber;
	statistics.resources.maxMemUsed = TestNumber;
	statistics.resources.maxMemUsed = TestNumber;
	statistics.resources.timeMemThreshold = TestNumber;
	statistics.resources.cpuUsed = TestNumber;
	statistics.resources.maxCpuAvg = TestNumber;
	statistics.resources.timeCpuThreshold = TestNumber;
	statistics.resources.interrupts = TestNumber;

	if(type == 1){
		statistics.socket.established = TestNumber;
		statistics.socket.listening = TestNumber;
		statistics.socket.connected = TestNumber;	
	}
	statistics.tracepoints.kfree_skb = TestNumber;
	statistics.tracepoints.consume_skb = TestNumber;

	statistics.vm = "VM";
	statistics.metric = TestNumber;
}

void info_settings::save(const std::string &filename)
{
    using boost::property_tree::ptree;
    ptree tree;
	/*FILE *file;
	if(file = fopen(filename.c_str(), "r")) {
	 	read_xml(filename, tree);
	  	ptree dataTree;
		dataTree.put("pdropped", pdropped);
		dataTree.put("reason", reason);
		dataTree.put("proto_details.protocol", protocol.protocol);
		dataTree.put("proto_details.sender", protocol.sender);
		dataTree.put("proto_details.receiver", protocol.receiver);
		dataTree.put("proto_details.windowSize", protocol.windowSize);
		dataTree.put("proto_details.errors.checksum", protocol.error.checkSum);
		dataTree.put("resources.Memory_used", resources.memory_used);
		dataTree.put("resources.CPU_used", resources.cpu_used);
		dataTree.put("resources.Sockets_used", resources.sockets_used);
		dataTree.put("resources.Interrupts", resources.interrupts);
		tree.add_child("statistics.info", dataTree);
	  	write_xml(filename, tree);
		fclose(file);
	}
	else{
		tree.put("statistics.info.pdropped", pdropped);
		tree.put("statistics.info.reason", reason);		
		tree.put("statistics.info.proto_details.protocol", protocol.protocol);
		tree.put("statistics.info.proto_details.sender", protocol.sender);
		tree.put("statistics.info.proto_details.receiver", protocol.receiver);
		tree.put("statistics.info.proto_details.windowSize", protocol.windowSize);
		tree.put("statistics.info.proto_details.errors.checksum", protocol.error.checkSum);
		tree.put("statistics.info.resources.Memory_used", resources.memory_used);
		tree.put("statistics.info.resources.CPU_used", resources.cpu_used);
		tree.put("statistics.info.resources.Sockets_used", resources.sockets_used);
		tree.put("statistics.info.resources.Interrupts", resources.interrupts);
	}*/
	//FILE *file;
	//file = fopen(filename.c_str(), "w");	
	tree.put("statistics.info.vm-name",vm);
	tree.put("statistics.info.metric",metric);
	

	tree.put("statistics.info.totalSend", totalSend);
	tree.put("statistics.info.totalRecv", totalRecv);	
	//tree.put("statistics.info.proto_details.errors.checksum", protocol.error.checkSum);

	tree.put("statistics.info.proto_details.ip.totalPacketsReceived", protocol.ip.totalReceived);
	tree.put("statistics.info.proto_details.ip.inAddrErrors", protocol.ip.inAddrErrors);
	tree.put("statistics.info.proto_details.ip.incomingPacketsDiscarded", protocol.ip.incomingDiscarded);
	tree.put("statistics.info.proto_details.ip.incomingPacketsDelivered", protocol.ip.incomingDelivered);
	tree.put("statistics.info.proto_details.ip.requestsSentOut", protocol.ip.requestsSentOut);
	tree.put("statistics.info.proto_details.ip.outgoingDropped", protocol.ip.outgoingDropped);
	tree.put("statistics.info.proto_details.ip.reasmTimeout", protocol.ip.reasmTimeout);
	tree.put("statistics.info.proto_details.ip.reasmReqds", protocol.ip.reasmReqds);
	tree.put("statistics.info.proto_details.ip.reasmOKs", protocol.ip.reasmOKs);
	tree.put("statistics.info.proto_details.ip.reasmFails", protocol.ip.reasmFails);
	tree.put("statistics.info.proto_details.ip.fragOKs", protocol.ip.fragOKs);
	tree.put("statistics.info.proto_details.ip.fragFails", protocol.ip.fragFails);
	tree.put("statistics.info.proto_details.ip.fragCreates", protocol.ip.fragCreates);

	tree.put("statistics.info.proto_details.tcp.activeConnections", protocol.tcp.activeConnections);
	tree.put("statistics.info.proto_details.tcp.failedConnections", protocol.tcp.failedConnections);
	tree.put("statistics.info.proto_details.tcp.segmentsRecv", protocol.tcp.segmentsRecv);
	tree.put("statistics.info.proto_details.tcp.segmentsSend", protocol.tcp.segmentsSend);
	tree.put("statistics.info.proto_details.tcp.badSegments", protocol.tcp.badSegments);
	tree.put("statistics.info.proto_details.tcp.resetsSent", protocol.tcp.resetsSent);

	tree.put("statistics.info.proto_details.udp.packetsReceived", protocol.udp.packetsReceived);
	tree.put("statistics.info.proto_details.udp.unknownPortRecv", protocol.udp.unknownPortRecv);
	tree.put("statistics.info.proto_details.udp.recvErrors", protocol.udp.recvErrors);
	tree.put("statistics.info.proto_details.udp.packetsSent", protocol.udp.packetsSent);

	tree.put("statistics.info.resources.Memory_used", resources.memUsed);
	tree.put("statistics.info.resources.MaxMemoryUsed", resources.maxMemUsed);
	tree.put("statistics.info.resources.MemOverThreshold", resources.timeMemThreshold);
	tree.put("statistics.info.resources.CPU_used", resources.cpuUsed);
	tree.put("statistics.info.resources.MaxCpuAvg", resources.maxCpuAvg);
	tree.put("statistics.info.resources.CpuOverThreshold", resources.timeCpuThreshold);
	tree.put("statistics.info.resources.Interrupts", resources.interrupts);

	tree.put("statistics.info.socket.established", socket.established);
	tree.put("statistics.info.socket.listening", socket.listening);
	tree.put("statistics.info.socket.connected", socket.connected);

	tree.put("statistics.info.tracepoints.kfree_skb", tracepoints.kfree_skb);
	tree.put("statistics.info.tracepoints.consume_skb", tracepoints.consume_skb);

	write_xml(filename, tree);
}
