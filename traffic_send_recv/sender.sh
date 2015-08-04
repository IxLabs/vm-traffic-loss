#!/bin/bash
#usage command len protocol destination port

if [[ "$1" == "netperf" ]]; then
	if [[ "$3" == "TCP" ]]; then
		eval "netperf -t TCP_STREAM -l "$2" -H "$4" -p "$5""
	else 
		eval "netperf -t UDP_STREAM -l "$2" -H "$4" -p "$5""
	fi
fi
				
