#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#define FILE_TYPE ".as"
#define FILE_TYPE_LEN strlen(FILE_TYPE)
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
char * get_filename(char *);
FILE * get_file(char *);
#endif /* FUNCTIONS_H */