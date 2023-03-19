# SS-CA-1
Project Requirements:
a. Create a daemon to continually manage the operation of the requirements listed by the CTO above.
b. Identify new or modified xml reports and log details of who made the changes, this should be generated as a text file report and stored on the server.
c. The department managers must upload their xml report file by 11.30pm each night. The uploads to the shared directory must be moved to the reporting directory. This should happen at 1am. (this functionality needs to be self contained in the solution. Don’t use cron)
d. If a file wasn’t uploaded this should be logged in the system. (A naming convention can be used to help with this task.)
e. When the backup/transfer begins no user should be able to modify either the upload or reporting directory.
f. It must be possible to ask the daemon to backup and transfer at any time.
g. IPC should be setup to allow all processes to report in on completion of a task. (success or failure)
h. Error logging and reporting should be included for all main tasks in the solution.
i. Create a makefile to manage the creation of the executables.