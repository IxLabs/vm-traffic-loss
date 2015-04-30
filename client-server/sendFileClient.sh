#!/bin/bash
cat info_settings_out.xml | grep -oP '(?<=<statistics>).*?(?=</statistics>)' 2>&1 | nc localhost 60000
