#define BMS_MAX_OPERATIONS      3

typedef void (*operation) (void);

typedef struct
{
    char argument;
    operation bmsOperation;
}BMS_Operations;

operation getOperation(int argc, char **argv);
