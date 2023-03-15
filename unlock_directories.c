#include <sys/types.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <syslog.h>

void unlock_directories() {
    pid_t pid;

    pid = fork();

    if(pid == -1) {
        syslog(LOG_ERR, "LOCK_DIRECTORIES: ERROR OCCURRED DURING FORK");
    } else if(pid == 0) {
        char *unlock_script = "/home/alex/Desktop/assignment/src/scripts/unlock_directories.sh";
        char *args[] = {"/bin/sh", unlock_script, NULL};
        
        execvp(args[0], args);
    } else {
        int status;

        if(wait(&status) == -1) {
            syslog(LOG_ERR, "unlock_directories: wait() failed");
        } // end if

        if( (WIFEXITED(status)) ) {
            if( WEXITSTATUS(status) != 0 ) {
                syslog(LOG_ERR, "ERROR UNLOCKING DIRECTORIES, STATUS %d",     WEXITSTATUS(status));
            } else {
                syslog(LOG_INFO, "DIRECTORIES HAVE BEEN UNLOCKED");
            } // end if else
        } // end if
    } // end if else
} // end unlock_directories
        