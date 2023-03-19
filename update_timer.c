#include <syslog.h>
#include <stdio.h>
#include <time.h>

void update_timer(struct tm *due_date) { // update the timer to the next day
	printf("CURRENT DAY IS %d; CHANGING TIMER TO TOMMOROW'S DAY", due_date -> tm_mday); // log success
	due_date -> tm_mday += 1; // increment the day by 1

	/* mktime will convert the struct due_date into normal date format
	   i.e. if day is greater than 31 will make it day 1 */
  	mktime(due_date); // convert the struct due_date into normal date format
	printf("TIMER UPDATED, DUE NEXT DAY, %d", due_date -> tm_mday); // log success
} // end update_timer