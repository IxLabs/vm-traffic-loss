#!/bin/bash
while true; do
	read -p "Enter command : " comm
	if [[ "$comm" == "exit" ]];
  		then 
			break
	fi
	read -p "Enter parameters : " params
	read -p "Destination for command : " dest
	echo "Executing "$comm" "$params" "$dest""
	final_comm="$comm $params"
	ssh "$dest" "$final_comm" "> comm_output 2>&1 &"
	echo "Command "$final_comm" was executed! at "$dest""	
done
