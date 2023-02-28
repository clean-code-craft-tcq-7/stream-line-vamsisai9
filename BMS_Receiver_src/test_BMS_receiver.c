
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "BMS_Receiver.h"
#include "test_BMS_Operations.h"
#include "test_BMS_ProcessSensorValues.h"
#include "test_BMS_ReadConsole.h"
#include "BMS_IO_Mock.h"

void testBmsReceiver()
{

}

void test_BMS_Receiver()
{
    printf("Running test cases for BMS sensor stream sender module...\n");
    
    testBMSOperations();
    testReadHeader();
    testReadSamples();
    testProcessSensorValues();
    testBmsReceiver();

    printf("All tests are successful\n");
}
