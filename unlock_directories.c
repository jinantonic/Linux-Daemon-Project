#include <sys/types.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <syslog.h>

void unlock_directories() { // unlock directories
    pid_t pid; // process id
    pid = fork(); // fork a child process

    if(pid == -1) { // if fork fails
        syslog(LOG_ERR, "LOCK_DIRECTORIES: ERROR OCCURRED DURING FORK"); // log error

    } else if(pid == 0) { // if fork succeeds
        char *unlock_script = "/home/jinapark/SS-CA-1-main/scripts/unlock_directories.sh"; // path to the script
        char *args[] = {"/bin/sh", unlock_script, NULL}; // array of arguments to be passed to the script
        execvp(args[0], args); // execvp() replaces the current process image with a new process image

    } else { // parent
        int status; // status of child process

        if(wait(&status) == -1) { // wait() suspends execution of the calling process until a child specified by pid argument has changed state
            syslog(LOG_ERR, "unlock_directories: wait() failed"); // log error
        } // end if
        
        if( (WIFEXITED(status)) ) { // if child process exited normally
            if( WEXITSTATUS(status) != 0 ) { // if child process exited with error
                syslog(LOG_ERR, "ERROR UNLOCKING DIRECTORIES, STATUS %d",     WEXITSTATUS(status)); // log error
            } else { // if child process exited successfully
                syslog(LOG_INFO, "DIRECTORIES HAVE BEEN UNLOCKED"); // log success
            } // end if else
        } // end if
    } // end if else
} // end unlock_directories