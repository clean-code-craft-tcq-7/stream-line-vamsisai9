#include "BMS_Receiver.h"

int readHeader(receiverDataSet *dataBuffer, bmsInputFuncPtr inputFuncPtr);
void readSamples(receiverDataSet *dataBuffer, bmsInputFuncPtr inputFuncPtr);
