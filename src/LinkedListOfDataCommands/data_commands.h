#ifndef ASSEMBLER_DATA_COMMANDS_H
#define ASSEMBLER_DATA_COMMANDS_H
#include "../Common/common.h"

typedef struct DataCommands {
    int address;
    int num;
    int character;
    line_type type;
    struct DataCommands* next;
} DataCommands;

void addToDataCommands(DataCommands**, int, line_type, int);
void printDataCommands(DataCommands**);

#endif //ASSEMBLER_DATA_COMMANDS_H
