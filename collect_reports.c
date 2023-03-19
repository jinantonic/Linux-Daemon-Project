#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <syslog.h>

void collect_reports(void) { // collect reports from upload directory
    pid_t  pid; // process id
    pid = fork(); // fork a child process
    
    if (pid == 0) { // child
        syslog(LOG_INFO, "COLLECTING REPORTS"); // log success
        char *args[] = {"/bin/sh", "/home/jinapark/SS-CA-1-main/scripts/collect_reports.sh", NULL}; // arguments to be passed to execvp
        execvp(args[0], args); // execute the script
        
    } else { // parent
        int status; // status of child process
                        
        if(wait(&status) == -1) { // wait for child process to finish
            syslog(LOG_ERR, "collect_reports.c: wait() failed"); // log error
        } // end if

        if( (WIFEXITED(status)) ) { // if child process exited normally
            if( WEXITSTATUS(status) != 0 ) { // if child process exited with error
                syslog(LOG_ERR, "ERROR COLLECTING REPORTS FROM UPLOAD DIRECTORY: STATUS %d", WEXITSTATUS(status)); // log error
            } else { // if child process exited successfully
                syslog(LOG_INFO, "Successfully collected reports from upload directory, STATUS %d", WEXITSTATUS(status)); // log success
            } // end if else
        } // end if
    } // end if else
} // end collect_reports
