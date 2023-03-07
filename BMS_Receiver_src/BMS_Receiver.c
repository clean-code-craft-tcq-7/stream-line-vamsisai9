#include <stdio.h>

#include "BMS_ReadConsole.h"
#include "BMS_Receiver.h"
#include "BMS_ProcessSensorValues.h"
#include "BMS_Receiver_IO.h"

bmsInputFuncPtr bmsInputFunc = getInputFromConsole;
bmsOutputFuncPtr bmsOutputFunc = printReceiverOutput;

void setStreamIoFunc(bmsInputFuncPtr inputFuncPtr, bmsOutputFuncPtr outputFuncPtr)
{
    bmsInputFunc = inputFuncPtr;
    bmsOutputFunc = outputFuncPtr;
}

void receiveStreamData()
{
    receiverDataSet sensorDataSet[MAX_SENSORS_SUPPORTED];
    
    int count = readHeader(sensorDataSet, bmsInputFunc);
    readSamples(sensorDataSet, bmsInputFunc);
    
    processSensorData(sensorDataSet, count, bmsOutputFunc);
}
