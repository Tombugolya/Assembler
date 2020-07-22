#ifndef COMMON_H
#define COMMON_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LABEL_CHARS 32
typedef enum {False, True} boolean;
typedef enum {CODE = 0, DATA = 1, STRING = 2} line_type;
typedef enum {
    IMMEDIATE = 0, DIRECT = 1, INDIRECT = 2, REGISTER = 3, ERROR = -1
} addressing_modes;
typedef enum {MOV = 0,
              CMP = 1,
              ADD = 2, SUB = 2,
              LEA = 4,
              CLR = 5, NOT = 5, INC = 5, DEC = 5,
              JMP = 9, BNE = 9, JSR = 9,
              RED = 12,
              PRN = 13,
              RTS = 14,
              STOP = 15}
              opcodes;
#endif /* COMMON_H */