#include <stdio.h>

#include "BMS_ReceiverOperations.h"


int main(int argc, char **argv)
{
    operation operationFunc;
    operationFunc = getOperation(argc, argv);

    if(operationFunc != NULL)
    {
        operationFunc();
    }
    else
    {
        printf("Invalid option\nTry -h for usage information\n");
    }
}
