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
typedef enum {MOV, CMP, ADD, SUB, LEA, CLR, NOT, INC, DEC, JMP, BNE, JSR, RED, PRN, RTS, STOP} opcodes;
#endif /* COMMON_H */