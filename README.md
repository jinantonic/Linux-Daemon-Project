# SS-CA-1
Project Requirements:
1. Create a daemon to continually manage the operation of the requirements listed by the CTO above.
2. Identify new or modified XML reports and log details of who made the changes, this should be generated as a text file report and stored on the server.
3. The department managers must upload their XML report file by 11.30 pm each night. The uploads to the shared directory must be moved to the reporting directory. This should happen at 1 am. (this functionality needs to be self-contained in the solution. Don’t use cron)
4. If a file wasn’t uploaded this should be logged in the system. (A naming convention can be used to help with this task.)
5. When the backup/transfer begins no user should be able to modify either the upload or reporting directory.
6. It must be possible to ask the daemon to back up and transfer at any time.
7. IPC should be set up to allow all processes to report on the completion of a task. (success or failure)
8. Error logging and reporting should be included for all main tasks in the solution.
9. Create a makefile to manage the creation of the executables.
