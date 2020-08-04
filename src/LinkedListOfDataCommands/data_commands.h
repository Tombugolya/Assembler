#ifndef ASSEMBLER_DATA_COMMANDS_H
#define ASSEMBLER_DATA_COMMANDS_H
#include "../Common/common.h"

typedef struct DeclarationCommands {
    int address;
    int num;
    int character;
    line_type type;
    struct DeclarationCommands* next;
} DeclarationCommands;

void addToDeclarationCommands(DeclarationCommands **list, int address, line_type type, int value);

void printDeclarationCommands(DeclarationCommands **list);

void updateDeclarationCommands(DeclarationCommands **list, int IC);

#endif //ASSEMBLER_DATA_COMMANDS_H
