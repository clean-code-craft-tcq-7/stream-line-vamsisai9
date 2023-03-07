#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "BMS_Receiver.h"

static int readAndSplitLine(char *inputLine, char **buffer)
{
    char *delimitFields = strtok(inputLine, ",");
    int count = 0;

    while ((delimitFields != NULL) && (count < MAX_SENSORS_SUPPORTED))
    {
        strcpy(buffer[count], delimitFields);

        if(delimitFields[strlen(delimitFields) - 1] == 0x0A)
        {
            char *lastCharPtr = buffer[count];
            lastCharPtr[strlen(delimitFields) - 1] = 0;
        }

        count++;
        delimitFields = strtok (NULL, ",");

    }

    return count;
}

static void fillSensorNameAddress(char **dataBuff, receiverDataSet *dataSetBuff)
{
    int index = 0;

    for(; index < MAX_SENSORS_SUPPORTED; index++)
    {
        memset(dataSetBuff[index].sensorName, 0, 50);
        dataBuff[index] = dataSetBuff[index].sensorName;
    }
}

static void fillSensorValueAddress(char **dataBuff)
{
    int index = 0;

    for(; index < MAX_SENSORS_SUPPORTED; index++)
    {
        dataBuff[index] = (char *)calloc(10, sizeof(char));
    }
}

static void clearSensorValueAddress(char **dataBuff)
{
    int index = 0;

    for(; index < MAX_SENSORS_SUPPORTED; index++)
    {
        free(dataBuff[index]);
    }
}

static void convertStringValuesToFloat(char **stringBuffer, receiverDataSet *dataBuffer, int fieldCount, int sampleCount)
{
    int index = 0;

    for(; index < fieldCount; index++)
    {
        dataBuffer[index].sensorValues[sampleCount] = atof(stringBuffer[index]);
        dataBuffer[index].sensorValueCount = sampleCount + 1;
    }
}

static int readSamplesFromLine(receiverDataSet *dataBuffer, int sampleCount, bmsInputFuncPtr inputFuncPtr)
{
    char lineData[100];
    char *lineFieldBuffer[MAX_SENSORS_SUPPORTED];
    int sensorCount = 0;
    
    memset(lineData, 0, 100);
    if(inputFuncPtr(lineData, 100) > 0)
    {
        fillSensorValueAddress(lineFieldBuffer);
        sensorCount = readAndSplitLine(lineData, lineFieldBuffer);
        convertStringValuesToFloat(lineFieldBuffer, dataBuffer, sensorCount, sampleCount);

        clearSensorValueAddress(lineFieldBuffer);
    }

    return sensorCount;
}

int readHeader(receiverDataSet *dataBuffer, bmsInputFuncPtr inputFuncPtr)
{
    char lineData[200];
    char *sensorNames[MAX_SENSORS_SUPPORTED];
    char sensorCount = 0;

    memset(lineData, 0, 200);
    if(inputFuncPtr(lineData, 200) > 0)
    {
        fillSensorNameAddress(sensorNames, dataBuffer);
        sensorCount = readAndSplitLine(lineData, sensorNames);
    }
    
    return sensorCount;
}

void readSamples(receiverDataSet *dataBuffer, bmsInputFuncPtr inputFuncPtr)
{
    int sampleIndex = 0;
    
    for(; sampleIndex < MAX_SENSOR_VALUES_SUPPORTED; sampleIndex++)
    {
        if(readSamplesFromLine(dataBuffer, sampleIndex, inputFuncPtr) == 0)
        {
            break;
        }
    }
}
