#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>

#include "BMS_IO_Mock.h"
#include "BMS_ProcessSensorValues.h"

extern int TestOutputSize;
extern char TestOutputBuffer[1000];

void testMovingAverage()
{
    receiverDataSet sensorData[3] = {{"sensor1", {20, 30, 20.5, 2.5, 8.5, 7.5, 6.5}, 7}, {"sensor2", {0.7, 0.3, 0.5, 0.5, 0.6, 0.9, 1.0}, 7}, {"sensor3", {100.1, 80.3, 20.5, 27.5, 78.5, 57.5, 46.5}, 7}};
    TestOutputSize = 0;
    memset(TestOutputBuffer, 0, 1000);
    findAndPrintMovingAverages(sensorData, 3, mockReceiverOutput);
    assert(TestOutputSize == 149);
    assert(strcmp(TestOutputBuffer, "sensor1 sensor Moving Averages:\n16.30 13.80 9.10 \nsensor2 sensor Moving Averages:\n0.52 0.56 0.70 \nsensor3 sensor Moving Averages:\n61.38 52.86 46.10 \n") == 0);

    TestOutputSize = 0;
    memset(TestOutputBuffer, 0, 1000);
    findAndPrintMovingAverages(sensorData, 0, mockReceiverOutput);
    assert(TestOutputSize == 0);

    receiverDataSet sensorData1[3] = {{"sensor1", {20, 30, 20.5, 2.5}, 4}, {"sensor2", {0.7, 0.3, 0.5, 1.0}, 4}, {"sensor3", {100.1, 80.3, 20.5, 27.5, 78.5, 57.5, 46.5}, 7}};
    TestOutputSize = 0;
    memset(TestOutputBuffer, 0, 1000);
    findAndPrintMovingAverages(sensorData1, 3, mockReceiverOutput);
    assert(TestOutputSize == 117);
    assert(strcmp(TestOutputBuffer, "sensor1 sensor Moving Averages:\n\nsensor2 sensor Moving Averages:\n\nsensor3 sensor Moving Averages:\n61.38 52.86 46.10 \n") == 0);

}

void testMinMaxFinder()
{
    receiverDataSet sensorData[3] = {{"sensor1", {20, 30, 20.5, 2.5, 8.5, 7.5, 6.5}, 7}, {"sensor2", {0.7, 0.3, 0.5, 0.5, 0.6, 0.9, 1.0}, 7}, {"sensor3", {100.1, 80.3, 20.5, 27.5, 78.5, 57.5, 46.5}, 7}};
    TestOutputSize = 0;
    memset(TestOutputBuffer, 0, 1000);
    findAndPrintMinMaxValues(sensorData, 3, mockReceiverOutput);
    assert(TestOutputSize == 190);
    assert(strcmp(TestOutputBuffer, "sensor1 sensor min Value: 2.50\nsensor1 sensor max Value: 30.00\nsensor2 sensor min Value: 0.30\nsensor2 sensor max Value: 1.00\nsensor3 sensor min Value: 20.50\nsensor3 sensor max Value: 100.10\n") == 0);

    TestOutputSize = 0;
    memset(TestOutputBuffer, 0, 1000);
    findAndPrintMinMaxValues(sensorData, 0, mockReceiverOutput);
    assert(TestOutputSize == 0);

    receiverDataSet sensorData1[3] = {{"sensor1", {20}, 1}, {"sensor2", {0.7}, 1}, {"sensor3", {100.1}, 1}};
    TestOutputSize = 0;
    memset(TestOutputBuffer, 0, 1000);
    findAndPrintMinMaxValues(sensorData1, 3, mockReceiverOutput);
    assert(TestOutputSize == 192);
    assert(strcmp(TestOutputBuffer, "sensor1 sensor min Value: 20.00\nsensor1 sensor max Value: 20.00\nsensor2 sensor min Value: 0.70\nsensor2 sensor max Value: 0.70\nsensor3 sensor min Value: 100.10\nsensor3 sensor max Value: 100.10\n") == 0);

}

void testSensorDataProcessor()
{
    receiverDataSet sensorData[3] = {{"sensor1", {20, 30, 20.5, 2.5, 8.5, 7.5, 6.5}, 7}, {"sensor2", {0.7, 0.3, 0.5, 0.5, 0.6, 0.9, 1.0}, 7}, {"sensor3", {100.1, 80.3, 20.5, 27.5, 78.5, 57.5, 46.5}, 7}};
    TestOutputSize = 0;
    memset(TestOutputBuffer, 0, 1000);
    processSensorData(sensorData, 3, mockReceiverOutput);
    assert(TestOutputSize == 339);
    assert(strcmp(TestOutputBuffer, "sensor1 sensor Moving Averages:\n16.30 13.80 9.10 \nsensor2 sensor Moving Averages:\n0.52 0.56 0.70 \nsensor3 sensor Moving Averages:\n61.38 52.86 46.10 \nsensor1 sensor min Value: 2.50\nsensor1 sensor max Value: 30.00\nsensor2 sensor min Value: 0.30\nsensor2 sensor max Value: 1.00\nsensor3 sensor min Value: 20.50\nsensor3 sensor max Value: 100.10\n") == 0);

    TestOutputSize = 0;
    memset(TestOutputBuffer, 0, 1000);
    processSensorData(sensorData, 0, mockReceiverOutput);
    assert(TestOutputSize == 0);

    receiverDataSet sensorData1[3] = {{"sensor1", {20, 30, 20.5, 2.5}, 4}, {"sensor2", {0.7, 0.3, 0.5, 1.0}, 4}, {"sensor3", {100.1, 80.3, 20.5, 27.5, 78.5, 57.5, 46.5}, 7}};
    TestOutputSize = 0;
    memset(TestOutputBuffer, 0, 1000);
    processSensorData(sensorData1, 3, mockReceiverOutput);
    assert(TestOutputSize == 307);
    assert(strcmp(TestOutputBuffer, "sensor1 sensor Moving Averages:\n\nsensor2 sensor Moving Averages:\n\nsensor3 sensor Moving Averages:\n61.38 52.86 46.10 \nsensor1 sensor min Value: 2.50\nsensor1 sensor max Value: 30.00\nsensor2 sensor min Value: 0.30\nsensor2 sensor max Value: 1.00\nsensor3 sensor min Value: 20.50\nsensor3 sensor max Value: 100.10\n") == 0);
}

void testProcessSensorValues()
{
    testMovingAverage();
    testMinMaxFinder();
    testSensorDataProcessor();
}
