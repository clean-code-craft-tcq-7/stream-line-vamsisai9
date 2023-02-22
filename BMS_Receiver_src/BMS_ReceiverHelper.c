#include <stdio.h>

void printHelpDocument()
{
    printf("BMS Receiver Application\n");
    printf("\t -r Run BMS receiver application. Receives csv formated data stream from Battery Management system, calculates Moving average, Min, Max values of each parameters\n");
    printf("\t -t Run unit test cases for BMS Receiver application\n");
    printf("\t -h helper for BMS Receiver application\n");
}
