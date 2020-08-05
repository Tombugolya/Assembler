#ifndef ASSEMBLER_DECODE_H
#define ASSEMBLER_DECODE_H
#include <stdarg.h>
#include "../LinkedListOfDataCommands/declaration_commands.h"
#include "../LabelChart/label_chart.h"
#include "../UtilFunctions/functions.h"

void decodeInstruction(InstructionData data, char *filename);

void writeOperand(Operand operand, char *name);

void reserveOperand(Operand operand, char *name);

void writeDistance(FILE *file, int addressOrigin, int addressDestination);

void writeExternal(FILE *file, int address);

void writeAddress(FILE *file, int addressOrigin, int labelAddress);

void writeICDC(char *name, int IC, int DC);

void writeData(DeclarationCommands **list, char *name);

void writeHexadecimal(int num, int address, char *name);

void writeToExtFile(char *filename, char *labelName, int address);

void writeToEntFile(char *filename, LabelChart **list);

#endif //ASSEMBLER_DECODE_H
