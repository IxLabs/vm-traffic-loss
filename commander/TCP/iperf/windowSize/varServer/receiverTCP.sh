#!/bin/bash
#usage ./receiver portNetperf portIperfUDP portIperfTCP TCPwindow

eval "sudo netserver -4 -p "$1"" > netperfLog
eval "sudo iperf -s -D -u -p "$2"" > iperfLogUDP
eval "sudo iperf -s -D -p "$3" "$4"" > iperfLogTCP

