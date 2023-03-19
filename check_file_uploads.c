#include <unistd.h>
#include <syslog.h>

void check_file_uploads(void) { // check if the files have been uploaded by the manager
   char *warehouse_xml = "/home/jinapark/SS-CA-1-main/reports/warehouse_report.xml"; // path to the xml files
   char *manufacturing_xml = "/home/jinapark/SS-CA-1-main/reports/manufacturing_report.xml";
   char *sales_xml = "/home/jinapark/SS-CA-1-main/reports/sales_report.xml";
   char *distribution_xml = "/home/jinapark/SS-CA-1-main/reports/distribution_report.xml";
   
   char *files[] = {warehouse_xml, manufacturing_xml, sales_xml, distribution_xml}; // array of the files

   syslog(LOG_INFO, "CHECKING FOR UPLOADED XML REPORTS"); // check for the files

   for (int i = 0; i < 4; ++i) { // iterate through the files
      if(access(files[i], F_OK) == -1) { // if the file doesn't exist,
         syslog(LOG_INFO,"File %s hasn't been uploaded by the manager", files[i]); // log that the file hasn't been uploaded
      } // end if
   } // end for
} // end check_file_uploads