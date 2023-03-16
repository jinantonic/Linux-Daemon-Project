date=$(date +'%d-%m-%Y')


tar -czf /Users/jinapark/SS-CA-1/report_backups/report_backups-${date}.tar.gz -C /Users/jinapark/SS-CA-1/dashboard --transform "s|dashboard|report_backups-${date}|" . == =