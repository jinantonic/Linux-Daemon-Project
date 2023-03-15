#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <syslog.h>

void collect_reports(void) {
    pid_t  pid;

    pid = fork();
    if (pid == 0) { // child
        syslog(LOG_INFO, "COLLECTING REPORTS");
        char *args[] = {"/bin/sh", "/home/alex/Desktop/assignment/src/scripts/collect_reports.sh", NULL};
        execvp(args[0], args);
    } else { // parent
        int status;
                        
        if(wait(&status) == -1) {
            syslog(LOG_ERR, "collect_reports.c: wait() failed");
        } // end if

        if( (WIFEXITED(status)) ) {
            if( WEXITSTATUS(status) != 0 ) {
                syslog(LOG_ERR, "ERROR COLLECTING REPORTS FROM UPLOAD DIRECTORY: STATUS %d", WEXITSTATUS(status));
            } else {
                syslog(LOG_INFO, "Successfully collected reports from upload directory, STATUS %d", WEXITSTATUS(status));
            } // end if else
        } // end if
    } // end if else
} // end collect_reports
