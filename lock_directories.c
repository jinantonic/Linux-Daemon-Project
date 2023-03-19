#include <sys/types.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <syslog.h>

void lock_directories() {
    pid_t pid; // process id
	pid = fork(); // fork a child process
	
	if(pid == -1) { // if fork fails
		syslog(LOG_ERR, "ERROR OCCURRED DURING FORK"); // log error

	} else if(pid == 0) { // if fork succeeds
		char *upload_dir = "/home/jinapark/SS-CA-1-main/reports"; // set upload directory
		char *dashboard_dir = "/home/jinapark/SS-CA-1-main/dashboard"; // set dashboard directory
	
		/* Set permissions.
		   Read and execute for user and group, other users have no permissions.
		   This will pevent any changes to be made to the dashboard and xml upload directories 
		   while the transfer and backup is happening. */
		char *args[] = {"/bin/chmod", "550", upload_dir, dashboard_dir, NULL}; // set arguments for chmod
		execvp(args[0], args); // execute chmod

	} else { // parent
        int status; // status of child process

        if(wait(&status) == -1) { // if wait fails
            syslog(LOG_ERR, "lock_directories: wait() failed"); // log error
        } // end if

        if( (WIFEXITED(status)) ) { // if child process exited normally
            if( WEXITSTATUS(status) != 0 ) { // if child process exited with error
                syslog(LOG_ERR, "ERROR LOCKING DIRECTORIES, STATUS %d", WEXITSTATUS(status)); // log error
            } else { // if child process exited successfully
                syslog(LOG_INFO, "DIRECTORIES HAVE BEEN LOCKED UNTIL BACKUP AND TRANSFER COMPLETES"); // log success
            } // end if else
        } // end if
	} // end if else
} // end lock_directories