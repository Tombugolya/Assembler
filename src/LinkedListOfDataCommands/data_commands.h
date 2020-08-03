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

void addToDataCommands(DataCommands **list, int address, line_type type, int value);

void printDataCommands(DataCommands **list);

void updateDataCommands(DataCommands **list, int IC);

#endif //ASSEMBLER_DATA_COMMANDS_H
