#ifndef ASSEMBLER_DECODE_H
#define ASSEMBLER_DECODE_H
#include <stdarg.h>
#include "../LinkedListOfDataCommands/data_commands.h"
#include "../UtilFunctions/functions.h"

typedef struct DataCode {
    unsigned int dataCode       : 24;
} DataCode;

void decodeInstruction(InstructionData, char *);
void writeOperand(Operand, char *);
void reserveOperand(Operand, char *);
void writeICDC(char *, int, int);
void writeData(DataCommands **, char *);
void writeHexadecimal(int, int, char * );
#endif //ASSEMBLER_DECODE_H
