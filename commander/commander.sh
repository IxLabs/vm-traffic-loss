#!/bin/bash
while true; do
	echo "Enter command : "
	read comm
	echo "$comm"
	if [[ "$comm" == "exit" ]];
  		then
			break
	fi
	echo "Enter parameters : "
	read params
	echo "$params"
	echo "Destination for command : "
	read dest
	echo "$dest"
	echo "Executing "$comm" "$params" with destination "$dest""
	final_comm="$comm $params"
	ssh -f -n "$dest" "$final_comm" "> comm_output 2>&1 &"
	echo "Command "$final_comm" was executed! at "$dest""
done
