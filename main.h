#ifndef ASSEMBLER_MAIN_H
#define ASSEMBLER_MAIN_H
#define FILE_TYPE ".as"
#define FILE_TYPE_LEN strlen(FILE_TYPE)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
enum {INPUT = 1};
char * get_filename(char *);
void file_management(int, char *[]);
void process_files(int, char *[]);
#endif //ASSEMBLER_MAIN_H
