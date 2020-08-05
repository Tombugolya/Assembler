#ifndef ASSEMBLER_DECLARATION_COMMANDS_H
#define ASSEMBLER_DECLARATION_COMMANDS_H
#include "../Common/common.h"

typedef struct DeclarationCommands {
    int address;
    int num;
    int character;
    line_type type;
    struct DeclarationCommands* next;
} DeclarationCommands;

void addToDeclarationCommands(DeclarationCommands **list, int address, line_type type, int value);

void updateDeclarationCommands(DeclarationCommands **list, int IC);

void freeDeclarationCommands(DeclarationCommands **list);

#endif //ASSEMBLER_DECLARATION_COMMANDS_H
