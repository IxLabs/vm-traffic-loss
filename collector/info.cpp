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
}

void info_settings::save(const std::string &filename)
{
    using boost::property_tree::ptree;
    ptree tree;
	FILE *file;
	if(file = fopen(filename.c_str(), "r")) {
	 	read_xml(filename, tree);
	  	ptree dataTree;
	  	dataTree.put("reason", reason);
		dataTree.put("pdropped", pdropped);
		dataTree.put("protocol.protocol", "foo");
		dataTree.put("protocol.sender", "senderFoo");
		dataTree.put("protocol.receiver", "receiverBar");
		tree.add_child("statistics.info", dataTree);
	  	write_xml(filename, tree);
		fclose(file);
	}
	else{
		tree.put("statistics.info.reason", reason);
		tree.put("statistics.info.pdropped", pdropped);
		tree.put("statistics.info.protocol.protocol", "foo");
		tree.put("statistics.info.protocol.sender", "senderFoo");
		tree.put("statistics.info.protocol.receiver", "receiverBar");
	}
	write_xml(filename, tree);
}
