#ifndef COMMON_H
#define COMMON_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../ErrorReport/error_report.h"

#define MAX_LINE_CHARS 82   /* '\n' + '\0' */
#define OPERATION_NUM 16
#define MAX_APPLICABLE_MODES 3
#define REGISTER_NUM 8

typedef enum {
    CODE = 0, NUMBER = 1, STRING = 2
} line_type;

typedef enum {
    ABSOLUTE, RELOCATABLE, EXTERNAL
} characterizationType;

typedef enum {
    IMMEDIATE = 0, DIRECT = 1, INDIRECT = 2, REGISTER = 3, end = 0
} addressing_mode;

typedef enum {
    EMPTY = -1,
    MOV = 0,
    CMP = 1,
    ADD = 2, SUB = 2,
    LEA = 4,
    CLR = 5, NOT = 5, INC = 5, DEC = 5,
    JMP = 9, BNE = 9, JSR = 9,
    RED = 12,
    PRN = 13,
    RTS = 14,
    STOP = 15
} opcodes;

typedef struct Operation {
    char *name;
    opcodes opCode;
    int function;
    int operands;
    addressing_mode modesDest[MAX_APPLICABLE_MODES];
    addressing_mode modesOrigin[MAX_APPLICABLE_MODES];
} Operation;

typedef struct InstructionData {
    int address;
    opcodes opCode;
    int function;
    addressing_mode dest;
    addressing_mode origin;
    int regisDest;
    int regisOrigin;
} InstructionData;

typedef struct Regis {
    char * name;
    int value;
} Regis;

extern const Regis registers[REGISTER_NUM];
extern const Operation operations[OPERATION_NUM];
#endif /* COMMON_H */
