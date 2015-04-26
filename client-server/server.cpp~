#include <stdio.h>
#include "iostream"
#include <stdlib.h>
#include <string>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

#define ServerPort	2100
#define maxAgents	10
#define MAXLEN		255
using namespace std;

/*structuri pentru datele despre pachete*/
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


/*structura folosita pentru transmiterea xml-ului*/
struct messageToSend
{
	int len;
	char buffer[256];
	int from;
	bool first;
};

int main(int argc, char *argv[])
{
	int sockfd, newsockfd, portno, n;
	socklen_t clilen;
	char buffer[256];			//bufferul folosit pentru trimitere
	struct sockaddr_in serv_addr, cli_addr;
	struct messageToSend m;		//structura ce se trimites
	string message;				//mesajul in care se aculumeaza
	int len;					// lungimea mesajului

	/*deschidere socket*/
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0){
		perror("ERROR opening socket");
		exit(1);	
	}
	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(ServerPort);
	
	if (bind(sockfd, (struct sockaddr *) &serv_addr, 
		sizeof(serv_addr)) < 0)
			perror("ERROR on binding");

	listen(sockfd, maxAgents);
	clilen = sizeof(cli_addr);
	newsockfd = accept(sockfd, 
		     (struct sockaddr *) &cli_addr, 
		     &clilen);
	if (newsockfd < 0) 
		perror("ERROR on accept");

	/*citire prim packet ce contine lungimea mesajului*/
	n = read(newsockfd,&m,sizeof(m));

	if(m.first)
		len = m.len;
	while(len >= 0)
	{
		n = read(newsockfd,&m,sizeof(m));
		if (n < 0)
			perror("ERROR reading from socket");
		len -= MAXLEN;
		message.append(string(m.buffer));
	}
	/*afiseaza xml-ul
	TODO	salvare xml si interpretat rezultate
	*/
	cout << message<<endl;
	close(newsockfd);
	close(sockfd);
	return 0; 
}
