#ifndef BMS_RECEIVER_H_
#define BMS_RECEIVER_H_

#define MAX_SENSOR_VALUES_SUPPORTED     50
#define MAX_SENSORS_SUPPORTED            10

#define MOVING_AVERAGE_STEPS            5

typedef int (*bmsInputFuncPtr)(char *, int);
typedef void (*bmsOutputFuncPtr)(char *, int);


typedef struct
{
    char sensorName[50];
    float sensorValues[MAX_SENSOR_VALUES_SUPPORTED];
    int sensorValueCount;

}receiverDataSet;

void receiveStreamData();

#endif
