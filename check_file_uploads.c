#include <unistd.h>
#include <syslog.h>

void check_file_uploads(void) {
   char *warehouse_xml = "/Users/jinapark/SS-CA-2/xml/warehouse_report.xml";
   char *manufacturing_xml = "/Users/jinapark/SS-CA-2/xml/manufacturing_report.xml";
   char *sales_xml = "/Users/jinapark/SS-CA-2/xml/sales_report.xml";
   char *distribution_xml = "/Users/jinapark/SS-CA-2/xml/distribution_report.xml";
   
   char *files[] = {warehouse_xml, manufacturing_xml, sales_xml, distribution_xml};

   syslog(LOG_INFO, "CHECKING FOR UPLOADED XML REPORTS");

   for(int i = 0; i < 4; ++i) {
      if(access(files[i], F_OK) == -1) {
         syslog(LOG_INFO,"File %s hasn't been uploaded by the manager", files[i]);
      } // end if
   } // end for
} // end check_file_uploads