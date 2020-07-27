#ifndef FIRST_ITERATION_H
#define FIRST_ITERATION_H
#include <ctype.h>
#include "../Common/common.h"

void first_iteration(char *, FILE *);
boolean is_label(const char token[], boolean);
boolean is_data(char *);
boolean is_command(char *);
boolean is_comment(const char *);
boolean is_extern();
boolean is_valid_data_name(char *);
boolean isValidNumber(char *);
boolean is_valid_operand(char *, int);
boolean isValidAddressingMode(addressing_mode mode, int operandNum);
boolean is_register(char *);
addressing_mode getOperandAddressingMode(char *);
void process_data_line(const char[], char*, boolean);
void process_extern_line(const char[], char*);
void process_command_line(char[], char*, boolean);
#endif /* FIRST_ITERATION_H */