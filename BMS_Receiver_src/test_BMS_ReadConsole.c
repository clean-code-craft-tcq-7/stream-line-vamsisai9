#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "BMS_IO_Mock.h"
#include "BMS_ReadConsole.h"
#include "BMS_Receiver.h"


extern int TestOutputSize;
extern char TestOutputBuffer[1000];

extern char TestInputArray[500];
extern int nextCharIndex;

void setTestInput(char *inputString)
{
    memset(TestInputArray, 0, 500);
    nextCharIndex = 0;
    strcpy(TestInputArray, inputString);

}

void testReadHeader()
{   
    receiverDataSet sensorData[MAX_SENSORS_SUPPORTED + 1];

    setTestInput("Temperature,ChargeRate,SOC,LeakageCurrent,TestSensor1,TestSensor2,TestSensor3,TestSensor4,TestSensor5,TestSensor6\n");

    assert(readHeader(sensorData, mockInputFromConsole) == 10);
    assert(strcmp(sensorData[0].sensorName, "Temperature") == 0);
    assert(strcmp(sensorData[1].sensorName, "ChargeRate") == 0);
    assert(strcmp(sensorData[2].sensorName, "SOC") == 0);
    assert(strcmp(sensorData[3].sensorName, "LeakageCurrent") == 0);
    assert(strcmp(sensorData[4].sensorName, "TestSensor1") == 0);
    assert(strcmp(sensorData[5].sensorName, "TestSensor2") == 0);
    assert(strcmp(sensorData[6].sensorName, "TestSensor3") == 0);
    assert(strcmp(sensorData[7].sensorName, "TestSensor4") == 0);
    assert(strcmp(sensorData[8].sensorName, "TestSensor5") == 0);
    assert(strcmp(sensorData[9].sensorName, "TestSensor6") == 0);

    setTestInput("Temperature,ChargeRate,SOC,LeakageCurrent,TestSensor1,TestSensor2,TestSensor3,TestSensor4,TestSensor5,TestSensor6,TestSensor7\n");
    memset(sensorData[10].sensorName, 0, 50);

    assert(readHeader(sensorData, mockInputFromConsole) == 10);
    assert(strcmp(sensorData[0].sensorName, "Temperature") == 0);
    assert(strcmp(sensorData[1].sensorName, "ChargeRate") == 0);
    assert(strcmp(sensorData[2].sensorName, "SOC") == 0);
    assert(strcmp(sensorData[3].sensorName, "LeakageCurrent") == 0);
    assert(strcmp(sensorData[4].sensorName, "TestSensor1") == 0);
    assert(strcmp(sensorData[5].sensorName, "TestSensor2") == 0);
    assert(strcmp(sensorData[6].sensorName, "TestSensor3") == 0);
    assert(strcmp(sensorData[7].sensorName, "TestSensor4") == 0);
    assert(strcmp(sensorData[8].sensorName, "TestSensor5") == 0);
    assert(strcmp(sensorData[9].sensorName, "TestSensor6") == 0);
    assert(strcmp(sensorData[10].sensorName, "") == 0);

    setTestInput("Temperature,ChargeRate\n");

    assert(readHeader(sensorData, mockInputFromConsole) == 2);
    assert(strcmp(sensorData[0].sensorName, "Temperature") == 0);
    assert(strcmp(sensorData[1].sensorName, "ChargeRate") == 0);

    setTestInput("ChargeRate12\n");

    assert(readHeader(sensorData, mockInputFromConsole) == 1);
    assert(strcmp(sensorData[0].sensorName, "ChargeRate12") == 0);

    setTestInput("");
    assert(readHeader(sensorData, mockInputFromConsole) == 0);

}

void testReadSamples()
{
    receiverDataSet sensorData[MAX_SENSORS_SUPPORTED + 1];

    setTestInput("1.2,23\n");

    readSamples(sensorData, mockInputFromConsole);
    assert(sensorData[0].sensorValueCount == 1);
    assert(fabs(sensorData[0].sensorValues[0] - 1.2) < 0.01);
    assert(sensorData[1].sensorValueCount == 1);
    assert(fabs(sensorData[1].sensorValues[0] - 23) < 0.01);

    setTestInput("25.7\n");

    readSamples(sensorData, mockInputFromConsole);
    assert(sensorData[0].sensorValueCount == 1);
    assert(fabs(sensorData[0].sensorValues[0] - 25.7) < 0.01);

    setTestInput("");
    sensorData[0].sensorValueCount = 0;

    readSamples(sensorData, mockInputFromConsole);
    assert(sensorData[0].sensorValueCount == 0);

    setTestInput("0.1,7.5\n23.5,0.1\n2.5,8.7\n");

    readSamples(sensorData, mockInputFromConsole);
    assert(sensorData[0].sensorValueCount == 3);
    assert(fabs(sensorData[0].sensorValues[0] - 0.1) < 0.01);
    assert(fabs(sensorData[0].sensorValues[1] - 23.5) < 0.01);
    assert(fabs(sensorData[0].sensorValues[2] - 2.5) < 0.01);
    assert(sensorData[1].sensorValueCount == 3);
    assert(fabs(sensorData[1].sensorValues[0] - 7.5) < 0.01);
    assert(fabs(sensorData[1].sensorValues[1] - 0.1) < 0.01);
    assert(fabs(sensorData[1].sensorValues[2] - 8.7) < 0.01);
}
