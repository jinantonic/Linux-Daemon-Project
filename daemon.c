/* 
   At 11:30 pm, there will be a check for the xml files that have been uploaded or files that have not been updated.
   At 1:00 am, the xml reports will be backed up from xml_upload_directory to dashboard_directory.
   
   Directories are locked during transfer / backup.

   Kill -2 signal will enable the daemon to transfer / backup at any given time.
*/

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <syslog.h>
#include <sys/stat.h>
#include <time.h>
#include "daemon_task.h"
#include <signal.h> 

int main() { // main function of daemon
   time_t now; // time_t is a type to represent time
   struct tm backup_time; // time to backup xml files
   time(&now); // get current time; same as: now = time(NULL)
   
   backup_time = *localtime(&now); // localtime converts a time_t value to calendar time, returns a pointer to a tm structure with its members filled with the corresponding values
   backup_time.tm_hour = 1; // set the time to 1:00 am
   backup_time.tm_min = 0;
   backup_time.tm_sec = 0; 

   // Implementation for Singleton Pattern if desired (Only one instance running)
   // Create a child process      
   int pid = fork(); // fork() creates a new process by duplicating the calling process

   if (pid > 0) { // parent process is running
      exit(EXIT_SUCCESS); // exit the parent process

   } else if (pid == 0) { // child process is running
      // Step 1: Create the orphan process
      // Step 2: Elevate the orphan process to session leader, to loose controlling TTY
      // This command runs the process in a new session
      if (setsid() < 0) { exit(EXIT_FAILURE); } // setsid() creates a new session if the calling process is not a process group leader

      int pid = fork(); // We could fork here again , just to guarantee that the process is not a session leader
      
      if (pid > 0) { // parent process is running
         exit(EXIT_SUCCESS); // exit the parent process
         
      } else { // child process is running
         umask(0); // Step 3: call umask() to set the file mode creation mask to 0

         // Step 4: Change the current working dir to root.
         // This will eliminate any issues of running on a mounted drive that potentially could be removed etc..
         if (chdir("/") < 0 ) { exit(EXIT_FAILURE); }

         // Step 5: Close all open file descriptors
         int x;
         for (x = sysconf(_SC_OPEN_MAX); x>=0; x--) { // sysconf() returns the value of the system variable name
            close (x); // close all file descriptors
         } // end for

         openlog("LOG-DAEMON", LOG_PID | LOG_CONS, LOG_DAEMON); // open the log file
         syslog(LOG_INFO, "DAEMON STARTED FOR MANUFACTURING COMPANY"); // log success
         
         struct tm check_uploads_time; // time to check for xml uploads
         time(&now);
         check_uploads_time = *localtime(&now); // localtime converts a time_t value to calendar time and returns a pointer to a tm structure with its members filled with the corresponding values
         check_uploads_time.tm_hour = 23; // set the time to 11:30 pm
         check_uploads_time.tm_min = 30; 
         check_uploads_time.tm_sec = 0;

         while(1) { 
            sleep(1); // sleep for 1 second

            if(signal(SIGINT, sig_handler) == SIG_ERR) { // if SIGINT is received, then call sig_handler
               syslog(LOG_ERR, "ERROR: daemon.c : SIG_ERR RECEIVED"); // log error
            } // end if
         
            // countdown to 23:30
            time(&now);
            double seconds_to_files_check = difftime(now,mktime(&check_uploads_time)); // difftime() returns the difference between time1 and time0, expressed in seconds

            if(seconds_to_files_check == 0) { // if seconds_to_files_check is 0,
               check_file_uploads(); // then it is time to check for xml uploads
               update_timer(&check_uploads_time); //change to tommorow's day
            } // end if
               
            // countdown to 1:00
            time(&now);
            double seconds_to_transfer = difftime(now, mktime(&backup_time));
           
            if(seconds_to_transfer == 0) { // if seconds_to_transfer is 0, then it is time to transfer xml files
               lock_directories(); // lock directories to prevent file corruption
               collect_reports(); // collect xml files from xml_upload_directory
               backup_dashboard(); // backup xml files from xml_upload_directory to dashboard_directory
               sleep(30); 
               unlock_directories(); // unlock directories
               generate_reports(); // generate reports from xml files
               update_timer(&backup_time); //after actions are finished, start counting to next day
            } // end if
         } // end while

         closelog(); // close the log file
         return 0;
      } // end if else
   } // end if else if
} // end main
