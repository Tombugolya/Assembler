#ifndef FIRST_ITERATION_H
#define FIRST_ITERATION_H
#include <ctype.h>
#include "../Common/common.h"

void firstIteration(char *, FILE *);
boolean isLabel(const char labelName[], boolean);
boolean isData(char *);
boolean isInstruction(char *);
boolean isComment(const char *);
boolean isExtern();
boolean isRegister(char *);
boolean isValidDataName(char *);
boolean isValidNumber(char *);
boolean isValidOperand(char *, int);
boolean isValidAddressingMode(addressing_mode mode, int operandNum);
addressing_mode getOperandAddressingMode(char *);
void processDataLine(const char[], char*, boolean);
void processExternLine(const char[], char*);
void processInstructionLine(char[], char*, boolean);
void resetValues();
#endif /* FIRST_ITERATION_H */
