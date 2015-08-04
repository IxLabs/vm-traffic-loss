#!/bin/bash
stat_file="current_status.xml"
tmp_output_file=$(mktemp)
while [ true ]; do
	netcat_nr=$(ps -ae | grep -Fx nc | wc -l)
	if [ $netcat_nr -eq 0 ]; then
		( head -n -1 "$stat_file"; nc -l -p 60000 ; echo "</statistics>" ) > "$tmp_output_file"
		mv "$tmp_output_file" "$stat_file"
	fi
done
