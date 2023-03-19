#ifndef DAEMON_TASKS 
#define DAEMON_TASKS

#include <time.h>

void collect_reports(void); // Collects reports from all the nodes

void backup_dashboard(void); // Backs up the dashboard

void lock_directories(void); // Locks the directories

void unlock_directories(void); // Unlocks the directories

void generate_reports(void); // Generates reports

void check_file_uploads(void); // Checks for file uploads

void sig_handler(int); // Signal handler

void update_timer(struct tm*); // Updates the timer
#endif