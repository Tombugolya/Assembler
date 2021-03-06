#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "../Common/common.h"
#include "../ErrorReport/error_report.h"

#define AS_EXTENSION ".as" /* Assembler file extension */

/* Function that opens the file and returns the file pointer
 * param file - the full name of the file
*/
FILE * getFile(char *file);

/* Function that returns the string without whitespaces before and after the actual content
 * param str - the string you would like to trim
*/
char * trimWhiteSpace(char *str);

/* Function that return a concatenated string from two string parameters
 * param s1 - the first string
 * param s2 - the second string
*/
char * concat(const char *s1, const char *s2);

/* Function that creates the initial test file the first iteration writes over
 * param name - the name of the file without the suffix
*/
void createTestFile(char *name);

/* Function that removes all of the program-created files
 * param name - the name of the file without the suffix
*/
void removeFiles(char *name);

/* Function that appends the relevant amount of decimal-converted bits to a string
 * param num - the decimal number to convert to binary
 * param bits - the amount of bits to append to the string
 * param str - the string to append the bits to
*/
void appendToBinaryString(unsigned int num, unsigned int bits, char *str);

/**/
int isFullLine(const char *line);

#endif
