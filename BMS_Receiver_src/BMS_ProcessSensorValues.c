#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "BMS_ProcessSensorValues.h"

static float findMinValue(float *dataBuffer, int count)
{
    int index = 0;
    float minValue = dataBuffer[0];

    for(;index < count; index++)
    {
        if(dataBuffer[index] < minValue)
        {
            minValue = dataBuffer[index];
        }
    }

    return minValue;
}

static float findMaxValue(float *dataBuffer, int count)
{
    int index = 0;
    float maxValue = dataBuffer[0];

    for(;index < count; index++)
    {
        if(dataBuffer[index] > maxValue)
        {
            maxValue = dataBuffer[index];
        }    
    }

    return maxValue;
}

static float findAverage(float *dataBuffer, int count)
{
    int index = 0;
    float sum = 0;

    for(;index < count; index++)
    {
        sum += dataBuffer[index];
    }

    return (sum / count);
}

static int findMovingAverage(float *dataBuffer, int count, float *movingAvrge, int movingAvrgeSize)
{
    int index = 0;

    while(index < (count - movingAvrgeSize + 1))
    {
        movingAvrge[index] = findAverage(&dataBuffer[index], movingAvrgeSize);
        index++;
    }
    
    return index;
}

void findAndPrintMovingAverages(receiverDataSet *sensorData, int sensorCount, bmsOutputFuncPtr outputFunc)
{
    int sensorIndex = 0, movingAvrgeCount = 0, movingAvrgeIndex = 0, printMsgSize = 0;
    float movingAverageBuff[MAX_SENSOR_VALUES_SUPPORTED];
    char printMsg[500] = {0};

    for(; sensorIndex < sensorCount; sensorIndex++)
    {
        movingAvrgeCount = findMovingAverage(sensorData[sensorIndex].sensorValues, sensorData[sensorIndex].sensorValueCount, movingAverageBuff, MOVING_AVERAGE_STEPS);
        
        printMsgSize += sprintf(&printMsg[printMsgSize], "%s sensor Moving Averages:\n", sensorData[sensorIndex].sensorName);

        for(movingAvrgeIndex = 0; movingAvrgeIndex < movingAvrgeCount; movingAvrgeIndex++)
        {
            printMsgSize += sprintf(&printMsg[printMsgSize], "%0.2f ", movingAverageBuff[movingAvrgeIndex]);
        }

        printMsgSize += sprintf(&printMsg[printMsgSize], "\n");
    }

    outputFunc(printMsg, printMsgSize);
}

void findAndPrintMinMaxValues(receiverDataSet *sensorData, int sensorCount, bmsOutputFuncPtr outputFunc)
{
    float minValue = 0, maxValue = 0;
    int sensorIndex = 0, printMsgSize = 0;
    char printMsg[500] = {0};

    for(; sensorIndex < sensorCount; sensorIndex++)
    {
        minValue = findMinValue(sensorData[sensorIndex].sensorValues, sensorData[sensorIndex].sensorValueCount);
        maxValue = findMaxValue(sensorData[sensorIndex].sensorValues, sensorData[sensorIndex].sensorValueCount);

        printMsgSize += sprintf(&printMsg[printMsgSize], "%s sensor min Value: %0.2f\n", sensorData[sensorIndex].sensorName, minValue);
        printMsgSize += sprintf(&printMsg[printMsgSize], "%s sensor max Value: %0.2f\n", sensorData[sensorIndex].sensorName, maxValue);
    }

    outputFunc(printMsg, printMsgSize);
}

void processSensorData(receiverDataSet *sensorData, int sensorCount, bmsOutputFuncPtr outputFunc)
{
    findAndPrintMovingAverages(sensorData, sensorCount, outputFunc);
    findAndPrintMinMaxValues(sensorData, sensorCount, outputFunc);
}
