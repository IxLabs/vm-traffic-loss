all:	info ifconfig collector
		g++ collector.o ifconfig.o info.o -o collector

info:
		g++ -std=c++11 -I ./../boost_1_57_0 -c info.cpp -o info.o

ifconfig:
		g++ -std=c++11 -c ifconfig.cpp -o ifconfig.o

collector:
		g++ -std=c++11 -c collector.cpp -o collector.o		

clean:
		rm -f collector *.o
