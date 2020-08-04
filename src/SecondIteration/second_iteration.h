#ifndef ASSEMBLER_SECOND_ITERATION_H
#define ASSEMBLER_SECOND_ITERATION_H
#include "../Common/common.h"
#include "../LabelChart/label_chart.h"
#include "../Decode/decode.h"

void second_iteration(char *filename, FILE *file, Label *labelHead);

boolean isEntry(char *entryName);

void processEntryLine(char *arguments, Label *labelHead);

void writeTestFileToOb(char *filename, Label *labelHead);

#endif //ASSEMBLER_SECOND_ITERATION_H
