#include <stdio.h>
#include "iostream"
#include <stdlib.h>
#include <unistd.h>
#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

#define ServerPort	2100
#define hostname	"victor-PC"
#define filename	"info_settings_out.xml"
#define MAXLEN		255
struct messageToSend
{
	int len;
	char buffer[256];
	int from;
	bool first;
};

using namespace std;

int main(int argc, char *argv[])
{	
	using boost::property_tree::ptree;
	int sockfd, portno, n;
	struct sockaddr_in serv_addr;
	struct hostent *server;
	char buffer[256];
    ptree tree;
	stringstream sstream;
	int length;
	string toSend;
	struct messageToSend m;
	int index;

	/*deschidere socket*/
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0){
		perror("ERROR opening socket");
		exit(1);
	}	
	server = gethostbyname(hostname);
	
	if (server == NULL) {
		fprintf(stderr,"ERROR, no such host\n");
		exit(0);
	}
	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	
	bcopy((char *)server->h_addr,
		(char *)&serv_addr.sin_addr.s_addr,
		server->h_length);

	serv_addr.sin_port = htons(ServerPort);
	if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
		perror("ERROR connecting");

	/*citire in stringstream-ul sstream tree-ul din xml*/
	read_xml(filename, tree);
	write_xml(sstream, tree);
	toSend = sstream.str();
	length = m.len = toSend.length();

	/*se trimite primul pachet ce contine lungimea intregului xml*/
	m.first = true;
	n = write(sockfd,&m,sizeof(m));
	if (n < 0) 
			perror("ERROR writing to socket");
	index = 0;
	while(length >= 0){		
		strcpy(m.buffer, toSend.substr(index, index+MAXLEN).c_str());
		n = write(sockfd,&m,sizeof(m));
		if (n < 0) 
			perror("ERROR writing to socket");
		length-=MAXLEN;
		index+=MAXLEN;
		m.first = false;
	}
	cout << "S-a trimis!"<<endl;
	close(sockfd);
	return 0;
}
