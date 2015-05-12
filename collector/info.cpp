#include "info.h"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

#define TestNumber 0

/*functii pentru salvare structuri info*/
void info_settings::load(const std::string &filename)
{
	std::cout << "Not Implemented yet!";
}

void initialize(info_settings& statistics){
	statistics.pdropped = 0;
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
		dataTree.put("proto_details.protocol", "foo");
		dataTree.put("proto_details.sender", "senderFoo");
		dataTree.put("proto_details.receiver", "receiverBar");
		dataTree.put("proto_details.windowSize", TestNumber);
		dataTree.put("proto_details.errors.checksum", TestNumber);
		dataTree.put("resources.Memory_used", TestNumber);
		dataTree.put("resources.CPU_used", TestNumber);
		dataTree.put("resources.Sockets_used", TestNumber);
		dataTree.put("resources.Interrupts", TestNumber);
		tree.add_child("statistics.info", dataTree);
	  	write_xml(filename, tree);
		fclose(file);
	}
	else{
		tree.put("statistics.info.pdropped", pdropped);
		tree.put("statistics.info.reason", reason);		
		tree.put("statistics.info.proto_details.protocol", "foo");
		tree.put("statistics.info.proto_details.sender", "senderFoo");
		tree.put("statistics.info.proto_details.receiver", "receiverBar");
		tree.put("statistics.info.proto_details.windowSize", TestNumber);
		tree.put("statistics.info.proto_details.errors.checksum", TestNumber);
		tree.put("statistics.info.resources.Memory_used", TestNumber);
		tree.put("statistics.info.resources.CPU_used", TestNumber);
		tree.put("statistics.info.resources.Sockets_used", TestNumber);
		tree.put("statistics.info.resources.Interrupts", TestNumber);
	}
	write_xml(filename, tree);
}
