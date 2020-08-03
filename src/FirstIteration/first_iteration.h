#ifndef FIRST_ITERATION_H
#define FIRST_ITERATION_H
#include <ctype.h>
#include "../Common/common.h"
#include "../UtilFunctions/functions.h"
#include "../LabelChart/label_chart.h"
#include "../LinkedListOfDataCommands/data_commands.h"
#include "../Decode/decode.h"
#include "../ErrorReport/error_report.h"
#define FIRST_PARAM paramNum == 1
#define SECOND_PARAM paramNum == 2
void firstIteration(char *, FILE *);
void createObFile(char *);
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
void processDataLine(char *, boolean);
void processExternLine(const char[]);
void processInstructionLine(char[], boolean, char *);
void resetValues();
#endif /* FIRST_ITERATION_H */
