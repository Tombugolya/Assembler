#ifndef ASSEMBLER_DECODE_H
#define ASSEMBLER_DECODE_H
#include <stdarg.h>
#include "../LinkedListOfDataCommands/data_commands.h"
#include "../UtilFunctions/functions.h"

typedef struct DataCode {
    unsigned int dataCode       : 24;
} DataCode;

void decodeInstruction(InstructionData data, char *filename);

void writeOperand(Operand operand, char *name);

void reserveOperand(Operand operand, char *name);

void writeICDC(char *name, int IC, int DC);

void writeData(DataCommands **list, char *name);

void writeHexadecimal(int num, int address, char *name);

#endif //ASSEMBLER_DECODE_H
