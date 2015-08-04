#!/bin/bash
#usage command time protocol destination port bandwidth/window_size packetsLen

if [[ "$1" == "netperf" ]]; then
	if [[ "$3" == "TCP" ]]; then
		eval "netperf -t TCP_STREAM -l "$2" -H "$4" -p "$5" -w "$6""
	else 
		eval "netperf -t UDP_STREAM -l "$2" -H "$4" -p "$5" -w "$6""
	fi
else
	if [[ "$3" == "TCP" ]]; then
		eval "iperf -t "$2" -c "$4" -p "$5" -w "$6""
	else
		eval "iperf -t "$2" -c "$4" -u -p "$5" -b "$6" -l "$7""
	fi
fi
				
