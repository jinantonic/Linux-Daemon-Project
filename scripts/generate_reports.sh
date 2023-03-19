#!/bin/bash

audit_file="audit-report-$(date +'%d-%m-%Y').txt"
syslog_report="syslog-report-$(date +'%d-%m-%Y').txt"

date=$(date +'%b %-d')

#generate audit log 
sudo ausearch -ts today -k folder-access | sudo aureport -f -i  > /home/jinapark/SS-CA-1-main/generate_reports/$audit_file

sudo cat /var/log/syslog |  grep -a "$date.*LOG-DAEMON" >  /home/jinapark/SS-CA-1-main/generate_reports/$syslog_report