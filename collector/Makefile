all:	info collector proc_stats netstat socket perf
		g++-4.9 -std=c++11 -pthread collector.o info.o proc_stats.o netstat.o socket_stats.o perf.o -o collector

perf:
		g++-4.9 -std=c++11 -c perf.cpp -o perf.o

socket:
		g++ -std=c++11 -c socket_stats.cpp -o socket_stats.o

netstat:
		g++-4.9 -std=c++11 -c netstat.cpp -o netstat.o

proc_stats:
		g++ -std=c++11 -c proc_stats.cpp -o proc_stats.o

info:
		g++ -std=c++11 -I ./../boost_1_57_0 -c info.cpp -o info.o

ifconfig:
		g++ -std=c++11 -c ifconfig.cpp -o ifconfig.o

collector:
		g++-4.9 -pthread -std=c++11 -c collector.cpp -o collector.o		

clean:
		rm -f collector *.o
