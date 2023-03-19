date=$(date +'%d-%m-%Y')


tar -czf /home/jinapark/SS-CA-1-main/report_backups/report_backups-${date}.tar.gz -C /home/jinapark/SS-CA-1-main/dashboard --transform "s|dashboard|report_backups-${date}|" .