#ifndef INFO_H
#define INFO_H

#include <stdio.h>
#include <string>
#include "iostream"

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

void initialize(info_settings& statistics);

#endif
