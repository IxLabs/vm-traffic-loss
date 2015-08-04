#include "socket_stats.h"

void getSocketInfo(struct info_settings &statistics, struct info_settings &first_stats){
	getInfo(statistics, first_stats, ESTABLISHED);
	getInfo(statistics, first_stats, LISTENING);
	getInfo(statistics, first_stats, CONNECTED);
	
}

void getInfo(struct info_settings &statistics, struct info_settings &first_stats, int mode){
	FILE *in;
	switch(mode){
	case ESTABLISHED:
					if(!(in = popen("netstat -an | grep ESTABLISHED | wc -l", "r"))) {
							cout<<"Eroare popen getSocketInfo"<<endl;
							return;
						}
					int es;
					fscanf(in, "%d", &es);
					//cout << "read now es = "<< es << endl;
					if( es >= first_stats.socket.established)
						statistics.socket.established += es - first_stats.socket.established;
					first_stats.socket.established = es;				
					fclose(in);
					break;
	case LISTENING:
					if(!(in = popen("netstat -an | grep LISTENING | wc -l", "r"))) {
							cout<<"Eroare popen getSocketInfo"<<endl;
							return;
						}
					int listening;
					fscanf(in, "%d", &listening);
					if( listening >= first_stats.socket.listening)
						statistics.socket.listening += listening - first_stats.socket.listening;
					first_stats.socket.listening = listening;
					fclose(in);
					break;
	case CONNECTED:
					if(!(in = popen("netstat -an | grep CONNECTED | wc -l", "r"))) {
							cout<<"Eroare popen getSocketInfo"<<endl;
							return;
						}
					int connected;
					fscanf(in, "%d", &connected);
					if( connected >= first_stats.socket.connected)
						statistics.socket.connected += connected - first_stats.socket.connected;	
					first_stats.socket.connected = connected;
					fclose(in);
					break;
	}
	
}
