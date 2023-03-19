#include <unistd.h>
#include <syslog.h>
#include "daemon_task.h"
#include <signal.h>
#include <stdlib.h>

void sig_handler(int sigNum) { // signal handler function
	if (sigNum == SIGINT) { // sudo kill -2 to collect the reports and backup the files
		syslog(LOG_INFO, "RECEIVED SIGNAL INTERRUPT, INITIATING BACKUP AND TRANSFER"); // log info
		lock_directories(); // lock directories to prevent file corruption
		collect_reports(); // collect xml files from xml_upload_directory
		backup_dashboard(); // backup xml files from xml_upload_directory to dashboard_directory
		sleep(30);
		unlock_directories(); // unlock directories 
		generate_reports(); // generate reports from xml files in dashboard_directory
	} // end if
} // end sig_handler