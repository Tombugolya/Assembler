#ifndef ASSEMBLER_DECODE_H
#define ASSEMBLER_DECODE_H
#include <stdarg.h>
#include "../Common/common.h"
typedef struct machineOperation {
    unsigned int external       : 1;
    unsigned int relocatable    : 1;
    unsigned int absolute       : 1;
    unsigned int function       : 5;
    unsigned int destOperand    : 3;
    unsigned int destAddress    : 2;
    unsigned int originOperand  : 3;
    unsigned int originAddress  : 2;
    unsigned int opCode         : 6;
} machineOperation;

typedef struct operandCode {
    unsigned int external       : 1;
    unsigned int relocatable    : 1;
    unsigned int absolute       : 1;
    unsigned int dataLine       : 21;
} operandCode;

typedef struct dataCode {
    unsigned int dataLine       : 24;
} dataCode;

int test(int);
void decode_to_binary(int, line_type, addressing_mode, ... );
void write_hexadecimal( machineOperation, char * );
#endif //ASSEMBLER_DECODE_H
