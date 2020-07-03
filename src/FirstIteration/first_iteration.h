#ifndef FIRST_ITERATION_H
#define FIRST_ITERATION_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../Common/common.h"
#define MAX_SYMBOL_CHARS 32
#define MAX_LINE_CHARS 82
void first_iteration(char *, FILE *);
boolean is_label(char token[]);
boolean is_data(char *);
boolean is_command(char *);
boolean is_comment(const char *);
boolean is_extern(char *);
boolean is_valid_data_name(char *);
void process_data_line(const char[], char*, boolean);
void process_extern_line(char[], char*);
void process_command_line(char[], char*, boolean);
#endif /* FIRST_ITERATION_H */