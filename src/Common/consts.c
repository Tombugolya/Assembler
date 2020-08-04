#include "common.h"

const char *delimiters = " \t\n"; /* These are essentially the whitespaces that we are trying to read-through*/

const Regis registers[] = {
        {"r0", 0},
        {"r1", 1},
        {"r2", 2},
        {"r3", 3},
        {"r4", 4},
        {"r5", 5},
        {"r6", 6},
        {"r7", 7},
};

const Operation operations[] = {
        {"mov", MOV, 0, 2 ,{DIRECT, REGISTER, end}, /* 'end' just pads the length of 3 array */
         {DIRECT, REGISTER, IMMEDIATE}},

        {"cmp", CMP, 0, 2 ,{DIRECT, REGISTER, IMMEDIATE},
                {DIRECT, REGISTER, IMMEDIATE}},

        {"add", ADD, 1, 2 ,{DIRECT, REGISTER, end},
                {DIRECT, REGISTER, IMMEDIATE}},

        {"sub", SUB, 2, 2 ,{DIRECT, REGISTER, end},
                {DIRECT, REGISTER, IMMEDIATE}},

        {"lea", LEA, 0, 2 ,{DIRECT, REGISTER, end},
                {DIRECT, end, end}},

        {"clr", CLR, 1, 1 ,{DIRECT, REGISTER, end},
                {end, end, end}},

        {"not", NOT, 2, 1 ,{DIRECT, REGISTER, end},
                {end, end, end}},

        {"inc", INC, 3, 1 ,{DIRECT, REGISTER, end},
                {end, end, end}},

        {"dec", DEC, 4, 1 ,{DIRECT, REGISTER, end},
                {end, end, end}},

        {"jmp", JMP, 1, 1 ,{DIRECT, INDIRECT, end},
                {end, end, end}},

        {"bne", BNE, 2, 1 ,{DIRECT, INDIRECT, end},
                {end, end, end}},

        {"jsr", JSR, 3, 1 ,{DIRECT, INDIRECT, end},
                {end, end, end}},

        {"red", RED, 0, 1 ,{DIRECT, REGISTER, end},
                {end, end, end}},

        {"prn", PRN, 0, 1 ,{DIRECT, REGISTER, end},
                {end, end, end}},

        {"rts", RTS, 0, 0 ,{end, end, end},
                {end, end, end}},

        {"stop", STOP, 0, 0 ,{end, end, end},
                {end, end, end}},
};
