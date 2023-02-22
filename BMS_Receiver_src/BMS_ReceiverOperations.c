#include <stdio.h>
#include <string.h>

#include "test_BMS_receiver.h"
#include "BMS_Receiver.h"
#include "BMS_ReceiverHelper.h"
#include "BMS_ReceiverOperations.h"

const BMS_Operations BMS_OperationConfig[BMS_MAX_OPERATIONS] = 
{
    { 'r', receiveStreamData},
    { 't', test_BMS_Receiver },
    { 'h', printHelpDocument}
};

static int checkArgumentCount(int argc)
{
    if(argc == 2)
    {
        return 1;
    }

    return 0;
}

static int isOperationRequestMatch(char *argv, char expKey)
{
    if(argv[0] == '-')
    {
        if(argv[1] == expKey)
        {
            return 1;
        }
    }

    return 0;
}

static operation checkOperation(char *argv)
{
    int index = 0;

    for(;index < BMS_MAX_OPERATIONS; index++)
    {
        if(isOperationRequestMatch(argv, BMS_OperationConfig[index].argument))
        {
            return BMS_OperationConfig[index].bmsOperation;
        }
    }

    return NULL;
}

operation getOperation(int argc, char **argv)
{
    if(checkArgumentCount(argc))
    {
        return checkOperation(argv[1]);
    }

    return NULL;
}
