#include <stdio.h>
#include <string.h>

int TestOutputSize;
char TestOutputBuffer[1000];

char TestInputArray[500];
int nextCharIndex = 0;

void mockReceiverOutput(char *ptr, int size)
{
    memset(TestOutputBuffer, 0, 1000);
    strncpy(TestOutputBuffer, ptr, size);
    TestOutputSize = size;
}

int mockInputFromConsole(char *ptr, int size)
{
    int charCount = 0;
    char *nextSlice = strtok(&TestInputArray[nextCharIndex], "\n");

    if(nextSlice != NULL)
    {
        charCount = strlen(nextSlice);
        nextCharIndex += charCount + 1;

        if(charCount > size)
        {
            charCount = size;
        }
        strncpy(ptr, nextSlice, charCount);
        ptr[charCount] = '\n';

    }
    
    return charCount;
}
