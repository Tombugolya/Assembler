#ifndef COMMON_H
#define COMMON_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LABEL_CHARS 32      /* 30 + '\n' + '\0' */
#define MAX_LINE_CHARS 82       /* 80 + '\n' + '\0' */
#define OPERATION_NUM 16        /* Number of operations (mov, jmp, etc.) */
#define MAX_APPLICABLE_MODES 3  /* Max number of supporting mods per operation */
#define REGISTER_NUM 8          /* Number of registers in use (r0, r1, ... ,r7) */
#define RESERVED_SIGN '?'       /* Sign that is used to identify reserved lines after first iteration */
#define TEST_EXTENSION ".test"
#define OB_EXTENSION ".ob"
#define EXT_EXTENSION ".ext"
#define ENT_EXTENSION ".ent"
#define COMMENT_SIGN ';'
#define DECLARATION_SIGN '.'
#define NUMBER_SIGN '#'
#define DISTANCE_SIGN '&'

/* boolean type for True and False*/
typedef enum {
    False, True
} boolean;

/* line_type type for the various lines that may show up on the user inputted file */
typedef enum {
    INSTRUCTION = 1, DATA = 2, STRING = 3, ENTRY = 4, EXTERN = 5
} line_type;

/* addressing_mode type for the various types of operands,
 * end - used only in consts file to signify that the specific operation has less than the MAX_APPLICABLE_MODES
 * ERROR - invalid mode
*/
typedef enum {
    IMMEDIATE = 0, DIRECT = 1, INDIRECT = 2, REGISTER = 3, ERROR = -1, end = -1
} addressing_mode;

/* opcodes type for the relevant decimal value per operation */
typedef enum {
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

/* Operation struct to represent each of the 16 constant operations
 * param name - the name of the operation (mov, jmp, etc.)
 * param opCode - the decimal value of the operation
 * param function - the decimal function value of the operation
 * param operands - the number of operands the operation supports (1, 2 or no operands)
 * param modesDest - array of up to 3 applicable modes for the destination operand
 * param modesOrigin - array of up to 3 applicable modes for the origin operand
*/
typedef struct Operation {
    char *name;
    opcodes opCode;
    int function;
    int operands;
    addressing_mode modesDest[MAX_APPLICABLE_MODES];
    addressing_mode modesOrigin[MAX_APPLICABLE_MODES];
} Operation;

/* Operand struct to represent the non-register operands from each Instruction line
 * param active - whether this operand is activated, IE non register operand and a relevant operand number
 * param value - the value that the operand is storing (-2, LABEL, &Distance, etc.)
 * param address - the address where the operand value will be stored
 * param reserve - reserve spot for the second iteration (if the operand is not an IMMEDIATE addressing mode)
*/
typedef struct Operand {
    boolean active;
    char *value;
    int address;
    boolean reserve;
} Operand;

/* InstructionData struct to represent the gathered information from each Instruction line
 * param address - the address in the memory for said instruction
 * param opCode - the relevant opCode value depending on the operation of the instruction line
 * param function - the relevant function value depending on the operation of the instruction line
 * param destMode - the addressing mode of the destination operand
 * param originMode - the addressing mode of the origin operand
 * param regisDest - the number of the selected destination register
 * param regisOrigin - the number of the selected origin register
*/
typedef struct InstructionData {
    int address;
    opcodes opCode;
    int function;
    addressing_mode originMode;
    addressing_mode destMode;
    int regisOrigin;
    int regisDest;
} InstructionData;

/* Register struct to represent each of the 8 constant registers
 * param name - the name of the register (r2, r0, etc.)
 * param value - the numerical value of the register (2 for r2, 1 for r1, etc.)
*/
typedef struct Register {
    char *name;
    int value;
} Register;

/* An array of 8 constant registers that our computer offers */
extern const Register REGISTERS[REGISTER_NUM];

/* An array of 16 constant operations that our assembler can read */
extern const Operation OPERATIONS[OPERATION_NUM];

/* The delimiters that are used for when we use strtok() */
extern const char *DELIMITERS;

/* A constant empty Instruction value, used for resetting variables of type InstructionData */
extern const InstructionData EMPTY_INSTRUCTION;

/* A constant empty Operand value, used for resetting variables of type Operand */
extern const Operand EMPTY_OPERAND;

#endif /* COMMON_H */
