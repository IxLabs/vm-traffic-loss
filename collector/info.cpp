#include "info.h"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

/*functii pentru salvare structuri info*/
void info_settings::load(const std::string &filename)
{
	std::cout << "Not Implemented yet!";
}

void initialize(info_settings& statistics){
	statistics.pdropped = 0;
	statistics.reason = "";	
	statistics.protocol.protocol = "fooProto";
	statistics.protocol.sender = "0.0.0.0";
	statistics.protocol.receiver = "0.0.0.0";
	statistics.protocol.windowSize = TestNumber;
	statistics.protocol.error.checkSum = TestNumber;
	statistics.resources.memory_used = TestNumber;
	statistics.resources.cpu_used = TestNumber;
	statistics.resources.sockets_used = TestNumber;
	statistics.resources.interrupts = TestNumber;
}

void info_settings::save(const std::string &filename)
{
    using boost::property_tree::ptree;
    ptree tree;
	FILE *file;
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
	}
	write_xml(filename, tree);
}
