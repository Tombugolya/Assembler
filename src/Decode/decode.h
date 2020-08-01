#ifndef ASSEMBLER_DECODE_H
#define ASSEMBLER_DECODE_H
#include <stdarg.h>
#include "../LinkedListOfDataCommands/data_commands.h"


typedef struct DataCode {
    unsigned int dataCode       : 24;
} DataCode;

void decodeInstruction(InstructionData, char *);
void writeOperand(char *, char *, int);
void reserveOperand(char *, char *, int);
void writeICDC(char *, int, int);
void writeData(DataCommands **, char *);
void writeHexadecimal(int, int, char * );
#endif //ASSEMBLER_DECODE_H
