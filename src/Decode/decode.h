#ifndef ASSEMBLER_DECODE_H
#define ASSEMBLER_DECODE_H
#include <stdarg.h>
#include "../Common/common.h"
struct machineOperation {
    unsigned int opCode         : 6;
    unsigned int originAddress  : 2;
    unsigned int originOperand  : 3;
    unsigned int destAddress    : 2;
    unsigned int destOperand    : 3;
    unsigned int function       : 5;
    unsigned int absolute       : 1;
    unsigned int relocatable    : 1;
    unsigned int external       : 1;
} machineOperation;

struct machineData {
    unsigned int dataLine       : 24;

} machineData;

void decode_to_binary(int, line_type, addressing_modes, ...);
#endif //ASSEMBLER_DECODE_H
