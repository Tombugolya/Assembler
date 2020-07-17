#ifndef FIRST_ITERATION_H
#define FIRST_ITERATION_H
#include <ctype.h>
#include "../Common/common.h"
#define MAX_LINE_CHARS 82

void first_iteration(char *, FILE *);
boolean is_label(const char token[]);
boolean is_data(char *);
boolean is_command(char *);
boolean is_comment(const char *);
boolean is_extern();
boolean is_valid_data_name(char *);
boolean is_valid_param(char *);
boolean is_valid_operand(char *, int);
boolean is_register(char *);
int get_operand_type(char *);
void process_data_line(const char[], char*, boolean);
void process_extern_line(const char[], char*);
void process_command_line(char[], char*, boolean);
#endif /* FIRST_ITERATION_H */