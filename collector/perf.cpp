#include "perf.h"

std::mutex mtx;

struct perf_stats stats;

void parse(std::string s1){
	std::istringstream iss(s1);
	double first;
	std::string type, second;
    iss>>first>>second>>type;
	//cout <<s1<< endl;
	int number = stringToNumber(second);
	if(type.compare("skb:kfree_skb") == 0){
		mtx.lock();
  		stats.kfree_skb += number;	
  		mtx.unlock();
	}
	else{
		mtx.lock();
		stats.consume_skb += number;
		mtx.unlock();
	}
}

void setPerfStats(struct info_settings &statistics){
	mtx.lock();
	//cout << "ajunge aici cu valorile "<<stats.kfree_skb<<" "<<stats.consume_skb<<endl;
	statistics.tracepoints.kfree_skb = stats.kfree_skb;
	statistics.tracepoints.consume_skb = stats.consume_skb;
	mtx.unlock();
}

void getPerf(int totalTime, string procPids){
	std::string command;
	if(procPids.compare("-a") != 0){
		command = "sudo perf stat -p "+procPids+" -I 5000 -e skb:kfree_skb  -e skb:consume_skb sleep "
				+std::to_string(totalTime)+"  2>&1 &";
	}
	else{
		command = "sudo perf stat -a -I 5000 -e skb:kfree_skb  -e skb:consume_skb sleep "
				+std::to_string(totalTime)+"  2>&1 &";
	}
	cout <<"Executing: "<< command << endl;
	FILE* pipe = popen(command.c_str(), "r");
	if (!pipe){
		cout <<"Error on getPerf() popen"<<endl;
		return;
	}
    char buffer[512];
	std::string s1;
	while(fgets(buffer, 512, pipe)){
		s1 = buffer;
		//cout << s1;
		parse(s1);
    }
	pclose(pipe);
    cout<<"Thread finished!"<< endl;
}

string getPidPerf(string pname){
	string perf = "pidof "+pname;
	char buffer[512];
	FILE* pipe = popen(perf.c_str(), "r");
	if(!pipe)
	{
		cout<<"Error in getting pidof process!"<<endl;
		return "";
	}
	string s1 = "";
	if(fgets(buffer, 512, pipe)){
		char *p = strtok(buffer, " \r\n");
		while (p && strcmp(p,"\n") != 0) {
		if(s1.compare("") == 0){
    		s1.append(p);
		}else{		
			s1.append(",");
			s1.append(p);
		}
		p = strtok (NULL, " ,.-\r\n");
		}
    }
	fclose(pipe);
	return s1;
}

bool is_number(const std::string& s)
{
    return !s.empty() && std::find_if(s.begin(), 
        s.end(), [](char c) { return !std::isdigit(c); }) == s.end();
}

int stringToNumber(string s){
	if(s.compare("") == 0 || s.compare("<not counted>") == 0){
		//cout<<"Error in getting number from string perf! "<<s<<endl;
		return 0;
	}
	//cout <<"aici sunt"<< s <<"aici ma termin"<< endl;
	string result = "";
	std::string::size_type sz;
	char* buf = strdup(s.c_str());
	char *p = strtok(buf, ".,- ");
	while (p) {
		result.append(p);
		p = strtok (NULL, " ,.-");
	}
	//cout <<"start=" << result <<"=end"<<endl;
	if(result.compare("<not") == 0 || result.compare("") == 0 || !is_number(result)){
		//cout<<"Error in getting number from string perf!"<<endl;
		return 0;	
	}
	return std::stoi (result,&sz);
}
