#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "../Common/common.h"
#include "../ErrorReport/error_report.h"

#define FILE_TYPE ".as"
#define FILE_TYPE_LEN strlen(FILE_TYPE)

char * getFilename(char *file);

FILE * getFile(char *file);

char * trimWhiteSpace(char *str);

void createObFile(char *name);

void removeFiles(char *name);

void appendToBinaryString(unsigned int x, unsigned int bits, char *string);

#endif /* FUNCTIONS_H */
