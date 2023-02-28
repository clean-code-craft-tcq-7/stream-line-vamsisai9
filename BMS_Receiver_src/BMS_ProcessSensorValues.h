#include "BMS_Receiver.h"

void findAndPrintMovingAverages(receiverDataSet *sensorData, int sensorCount, bmsOutputFuncPtr outputFunc);
void findAndPrintMinMaxValues(receiverDataSet *sensorData, int sensorCount, bmsOutputFuncPtr outputFunc);
void processSensorData(receiverDataSet *sensorData, int sensorCount, bmsOutputFuncPtr outputFunc);
