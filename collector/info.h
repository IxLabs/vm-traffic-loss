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

struct resourcesUsed
{
	public:
		int memory_used;
		int cpu_used;
		int sockets_used;
		int interrupts;
};

struct prot_details
{
	public:
		string protocol;
		string sender;
		string receiver;
		int windowSize;
		struct proto_errors error;	
};

struct info_settings
{
	int pdropped;
	string reason;
	struct prot_details protocol;
	struct resourcesUsed resources;
	void load(const std::string &filename);
	void save(const std::string &filename);
};

void initialize(info_settings& statistics);

#endif
