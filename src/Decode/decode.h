#ifndef ASSEMBLER_DECODE_H
#define ASSEMBLER_DECODE_H
#include <stdarg.h>
#include "../Common/common.h"

typedef struct InstructionCode {
    unsigned int external       : 1;
    unsigned int relocatable    : 1;
    unsigned int absolute       : 1;
    unsigned int function       : 5;
    unsigned int destOperand    : 3;
    unsigned int destAddress    : 2;
    unsigned int originOperand  : 3;
    unsigned int originAddress  : 2;
    unsigned int opCode         : 6;
} InstructionCode;

typedef struct OperandCode {
    unsigned int external       : 1;
    unsigned int relocatable    : 1;
    unsigned int absolute       : 1;
    unsigned int dataCode       : 21;
} OperandCode;

typedef struct DataCode {
    unsigned int dataCode       : 24;
} DataCode;

void decodeInstruction(int, line_type, addressing_mode, ... );
void writeHexadecimal(InstructionCode, char * );
#endif //ASSEMBLER_DECODE_H
