#!/bin/bash

#usage
#start the receiver first which will listen to 60000 port
#give the adress of listening netcat server ./senderFileClient address

cat info_settings_out.xml | grep -oP '(?<=<statistics>).*?(?=</statistics>)' 2>&1 | nc $1 60000
