#include <sys/types.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <syslog.h>

void lock_directories() {
    pid_t pid;

	pid = fork();

	if(pid == -1) { 
		syslog(LOG_ERR, "ERROR OCCURRED DURING FORK");
	} else if(pid == 0) { 
		char *upload_dir = "/home/alex/Desktop/assignment/managers_xml_upload";
		char *dashboard_dir = "/home/alex/Desktop/assignment/dashboard_system";
	
		//set permissions
		//read and execute for user and group 
		//other users have no permissions 
		//this will pevent any changes to be made to the dashboard 
		//and 
		//xml upload directories while the transfer and backup is happening	
		char *args[] = {"/bin/chmod", "550", upload_dir, dashboard_dir, NULL};

		execvp(args[0], args);
	} else {
        int status;

        if(wait(&status) == -1) {
                syslog(LOG_ERR, "lock_directories: wait() failed");
        } // end if

        if( (WIFEXITED(status)) ) {
            if( WEXITSTATUS(status) != 0 ) {
                    syslog(LOG_ERR, "ERROR LOCKING DIRECTORIES, STATUS %d", WEXITSTATUS(status));
            } else {
                    syslog(LOG_INFO, "DIRECTORIES HAVE BEEN LOCKED UNTIL BACKUP AND TRANSFER COMPLETES");
            } // end if else
        } // end if
	} // end if else
} // end lock_directories