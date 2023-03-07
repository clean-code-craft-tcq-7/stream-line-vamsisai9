
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "BMS_Receiver.h"
#include "test_BMS_Operations.h"
#include "test_BMS_ProcessSensorValues.h"
#include "test_BMS_ReadConsole.h"
#include "BMS_IO_Mock.h"
#include "BMS_Receiver_IO.h"

extern int TestOutputSize;
extern char TestOutputBuffer[1000];

void testBmsReceiver()
{
    setStreamIoFunc(mockInputFromConsole, mockReceiverOutput);
    setTestInput("Temperature,ChargeRate\n0.1,7.5\n23.5,0.1\n2.5,8.7\n2.5,10.6\n0.7,7.5\n");
    TestOutputSize = 0;
    memset(TestOutputBuffer, 0, 1000);

    receiveStreamData();
    assert(TestOutputSize == 223);
    assert(strcmp(TestOutputBuffer, "Temperature sensor Moving Averages:\n5.86 \nChargeRate sensor Moving Averages:\n6.88 \nTemperature sensor min Value: 0.10\nTemperature sensor max Value: 23.50\nChargeRate sensor min Value: 0.10\nChargeRate sensor max Value: 10.60\n") == 0);

    setTestInput("");
    TestOutputSize = 0;
    memset(TestOutputBuffer, 0, 1000);

    receiveStreamData();
    assert(TestOutputSize == 0);

    setTestInput("Temperature,ChargeRate\n0.1,7.5\n");
    TestOutputSize = 0;
    memset(TestOutputBuffer, 0, 1000);

    receiveStreamData();
    assert(TestOutputSize == 211);
    assert(strcmp(TestOutputBuffer, "Temperature sensor Moving Averages:\n\nChargeRate sensor Moving Averages:\n\nTemperature sensor min Value: 0.10\nTemperature sensor max Value: 0.10\nChargeRate sensor min Value: 7.50\nChargeRate sensor max Value: 7.50\n") == 0);


    setStreamIoFunc(getInputFromConsole, printReceiverOutput);

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
