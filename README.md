# Linux Daemon Project
## Project Overview
This project implements a daemon to manage XML report uploads and generate logs for an organisation's reporting system. The daemon ensures timely uploads, processes XML reports, and maintains a secure environment for data handling.

## Features
- Continuously monitors XML report uploads by department managers.
- Logs changes to XML reports, including details of modifications and the users responsible.
- Moves uploaded XML reports to a reporting directory at 1 AM daily.
- Records any missed uploads and logs this information.
- Prevents modifications to upload and reporting directories during backup and transfer processes.
- Allows manual triggering of backup and transfer operations.
- Utilises Inter-Process Communication (IPC) for task completion reporting.
- Includes comprehensive error logging and reporting for all main tasks.

## Project Requirements
1. Create a daemon to manage the operation of the system requirements.
2. Identify new or modified XML reports and log change details in a text file report.
3. Manage the upload of XML report files by department managers by 11:30 PM daily, moving them to the reporting directory at 1 AM without using cron.
4. Log any files that weren't uploaded using a naming convention.
5. Ensure no user can modify the upload or reporting directory during backup/transfer.
6. Provide a way to trigger backup and transfer at any time.
7. Implement IPC for process reporting on task completion.
8. Include error logging and reporting for all main tasks.
9. Create a Makefile to manage the creation of executables.

## Installation
To build the project, follow these steps.
1. Clone the repository:
   git clone https://github.com/yourusername/xml-report-daemon.git
   \ncd xml-report-daemon
3. Compile the code using the Makefile:
   make

## Usage
To run the daemon, execute the following command:
./daemon

## Commands
- To manually trigger a backup and transfer, send a specific signal to the daemon (e.g., `SIGUSR1`).
- Check the logs for any errors or status updates.

## Logging
Logs are stored in the `logs/` directory. Change details, missed uploads, and errors are recorded in separate log files for easy monitoring.
