#include <stdio.h>
#include <string.h>

void printReceiverOutput(char *ptr, int size)
{
    printf("%s", ptr);
}

int getInputFromConsole(char *ptr, int size)
{
    int inputSize = 0;

    memset(ptr, 0, size);
    
    if(fgets(ptr, size, stdin) != NULL)
    {
        inputSize = strlen(ptr);
    }

    return inputSize;
}
