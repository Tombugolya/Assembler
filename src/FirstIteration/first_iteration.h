#ifndef FIRST_ITERATION_H
#define FIRST_ITERATION_H
#include <ctype.h>
#include "../Common/common.h"
#include "../UtilFunctions/functions.h"
#include "../LabelChart/label_chart.h"
#include "../LinkedListOfDataCommands/data_commands.h"
#include "../Decode/decode.h"
#include "../ErrorReport/error_report.h"
#define FIRST_OPERAND operandNum == 1
#define SECOND_OPERAND operandNum == 2

void firstIteration(char *filename, FILE *file);

boolean isLabel(char *labelName, boolean toCheckColon);

boolean isData(char *dataName);

boolean isInstruction(char *commandName, boolean report);

boolean isComment(const char *commentSymbol);

boolean isExtern();

boolean isRegister(char *regis, boolean assign);

boolean isValidDataName(char *dataName);

boolean isValidNumber(char *number);

boolean isValidOperand(char *operand, int maxParamNum);

boolean isValidAddressingMode(addressing_mode mode, int operandNum);

addressing_mode getOperandAddressingMode(char *operand);

void processDeclarationLine(char *arguments);

void processString(char *arguments);

void processData(char *arguments);

void processExternLine(char *arguments);

void processInstructionLine(char *arguments, char *filename);

void handleOperands(char *filename);

void assignOperandValues(Operand *operand, boolean reserve, addressing_mode, char *value);

void assignInstructionValues();

void resetValues();

#endif /* FIRST_ITERATION_H */
