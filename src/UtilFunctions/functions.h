#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "../Common/common.h"

#define FILE_TYPE ".as"
#define FILE_TYPE_LEN strlen(FILE_TYPE)

char * getFilename(char *);
FILE * getFile(char *);
#endif /* FUNCTIONS_H */
