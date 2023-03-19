#include <time.h>
#include <unistd.h>
#include <stdio.h>
#include <syslog.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

void backup_dashboard(void) {
    pid_t  pid; // process id
	pid = fork(); // fork a child process
	
	if (pid == 0) { // child
		char *args[] = { // arguments to be passed to execvp
			"/bin/sh",
			"/home/jinapark/SS-CA-1-main/scripts/backup_reports.sh",				   NULL 
		}; // end args

		execvp(args[0], args); // execute the script
		syslog(LOG_INFO, "AFTER EXEC"); // should not reach this line

	} else { // parent
		int status; // status of child process
		
		if(wait(&status) == -1) { // wait for child process to finish
			syslog(LOG_ERR, "backup_dashboard.c: wait() failed"); // log error
		} // end if

		if( (WIFEXITED(status)) ) { // if child process exited normally
			if( WEXITSTATUS(status) != 0 ) { // if child process exited with error
				syslog(LOG_ERR, "ERROR BACKING UP DASHNBOARD DIRECTORY; STATUS %d", WEXITSTATUS(status)); // log error
			} else { // if child process exited successfully
				syslog(LOG_INFO, "Successfully backed up dashboard, STATUS %d", WEXITSTATUS(status)); // log success
			} // end if else
		} // end if
	} // end if else
} // end backup_dashboard