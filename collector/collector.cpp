#include "iostream"
#include <stdio.h>
#include <string>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <thread>
#include <chrono> 
#include <set>
#include <exception>

#define ifconfigRxInf	"RX packets:"
#define ifconfigTxInf	"TX packets:"
#define ifconfigTxSup	"carrier"

using namespace std;

struct prot_details
{
	public:
		string protocol;
		string sender;
		string receiver;
};

struct info_settings
{
	int pdropped;
	string reason;
	struct prot_details protocol;
	void load(const std::string &filename);
	void save(const std::string &filename);
};

/*functii pentru salvare structuri info*/
void info_settings::load(const std::string &filename)
{
	cout << "Not Implemented yet!";
}

void info_settings::save(const std::string &filename)
{
    using boost::property_tree::ptree;
    ptree tree;
	
	if(FILE *file = fopen(filename.c_str(), "r")) {
	 	read_xml(filename, tree);
	  	ptree dataTree;
	  	dataTree.put("reason", reason);
		dataTree.put("pdropped", pdropped);
		dataTree.put("protocol.protocol", "");
		dataTree.put("protocol.sender", "");
		dataTree.put("protocol.receiver", "");
		tree.add_child("statistics.info", dataTree);
	  	write_xml(filename, tree);
	}
	else{
		tree.put("statistics.info.reason", reason);
		tree.put("statistics.info.pdropped", pdropped);
		tree.put("statistics.info.protocol.protocol", "");
		tree.put("statistics.info.protocol.sender", "");
		tree.put("statistics.info.protocol.receiver", "");
	}
	write_xml(filename, tree);
}

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

void initialize(info_settings& statistics){
	statistics.pdropped = 0;
}

int main(int argc,char **argv ) {
	FILE *in;
	char buffer[512];
	string interface;
	struct info_settings statistics;
	struct info_settings last_stats;
	bool firstTime = true;
	int delay = atoi(argv[1]);
	initialize(statistics);
	initialize(last_stats);
	
	while(true){
		if(!(in = popen("ifconfig", "r"))) {
			cout<<"Eroare popen"<<endl;
			return -1;
		}

		while(fgets(buffer, sizeof(buffer), in) != NULL ) {
			if(strcmp(buffer, "\n") != 0) {
				interface.append(buffer);
			}
			else {
				parseInfo_ifconfig(statistics, interface);
				interface = "";
				}	
		}
		try
		{	if(!firstTime){
				statistics.pdropped -= last_stats.pdropped;
			}
			else{
				firstTime = false;
			}
			if(statistics.pdropped != 0){
				statistics.save("info_settings_out.xml");
				last_stats.pdropped += statistics.pdropped;
			}
		}
		catch (std::exception &e)
		{
			cout << "Error: " << e.what() << "\n";
		}
		initialize(statistics);
		pclose(in);
		this_thread::sleep_for (std::chrono::seconds(delay));
	}	
}
