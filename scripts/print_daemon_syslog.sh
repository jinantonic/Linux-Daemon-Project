#!/bin/sh

date=$(date +'%b  %-d')


sudo cat /var/log/daemon.log | grep -a "$date.*MAN-DAEMON-LOGGER"



