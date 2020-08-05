#ifndef FIRST_ITERATION_H
#define FIRST_ITERATION_H
#include <ctype.h>
#include "../Common/common.h"
#include "../UtilFunctions/functions.h"
#include "../LabelChart/label_chart.h"
#include "../LinkedListOfDataCommands/declaration_commands.h"
#include "../Decode/decode.h"
#include "../ErrorReport/error_report.h"
#include "../SecondIteration/second_iteration.h"

#define ORIGIN (operandNum == 1 && commandPointer -> operands == 2)
#define DESTINATION (operandNum == 2 || operandNum == 1 && commandPointer -> operands == 1)

/* The first iteration over a user inputted file.
 * The function iterates over each line and does the relevant action for each scenario.
 * During the parsing - the translated machine code is written on a temporary ".test" file.
 * Instruction lines are written on the fly.
 * Declaration lines are gathered in a DeclarationCommands linked list and are written after the first iteration is over.
 * By the end of the first iteration - all but the DIRECT/INDIRECT mode operands are decoded.
 * param filename - the name of the file without the suffix
 * param file - the user inputted file to read
*/
void firstIteration(char *filename, FILE *file);

/**/
void readFileLineByLineFirstTime(char *filename, FILE *file);

/* Checks if the first parameter matches the correct LABEL syntax
 * param labelName - the token from the line to check if it is in the correct LABEL: syntax
 * param toCheckColon - condition to check if the ':' appears at the end of the label
*/
boolean isLabel(char *labelName, boolean toCheckColon, boolean report);

/* Checks if the line is a potential declaration line, meaning it begins with a '.'.
 * The function is combined with isValidDeclarationName()
 * param declarationName - the token to check if it is a potential declaration line
*/
boolean isDeclaration(char *declarationName);

/* Checks if the line is a potential instruction line, meaning it matches any constant instruction operation (mov, cmp, etc.)
 * param commandName - the token to check if it matches any known operation
 * param report - condition to report on a non-match
*/
boolean isInstruction(char *commandName, boolean report);

/* Checks if the line is a comment, i.e begins with a semicolon ';'
 * param commentSymbol - the toke nto check if it starts with a semicolon
*/
boolean isComment(const char *commentSymbol);

/* Checks if the declaration line is an .extern declaration */
boolean isExtern();

/* Checks if the parameter matches any known register name.
 * If the condition is true -- a pointer is pointed towards to relevant constant register
 * param regis - the token to check whether its name matches a constant register
 * param assign - whether to point towards to the constant register or not
*/
boolean isRegister(char *regis, boolean assign);

/* Checks if the parameter matches any known declaration command (.string, .data, .entry, .extern)
 * param declarationName - the token to check the condition
*/
boolean isValidDeclarationName(char *declarationName);

/* Checks if the parameter is a valid syntax whole number (-2, 2, +3)
 * param number - the param to check the condition
*/
boolean isValidNumber(char *number);

/* Checks the following:
 * 1) Checks that the number of operands match with the instruction Operation.operands value
 * 2) Checks that the operands mode (destination and origin) match that of the instruction operation
 * 3) Checks that the syntax of the operands is correct
 * 4) Checks if the operands are properly comma separated
 * param operand - the first operand, later strtok'ed to the second operand (if relevant)
 * param maxParamNum - the relevant instruction Operation.operands value
*/
boolean isValidOperand(char *operand, int maxParamNum);

/* Checks that the addressing mode for the relevant operand matches any of the ones the Operation supports
 * param mode - the addressing mode to check
 * param operandNum - 1 = Destination operand ; 2 = Origin operand
*/
boolean isValidAddressingMode(addressing_mode mode, int operandNum);

/* Checks if the operand syntax matches any one of the addressing_modes, and returns it
 * param operand - the operand to check
*/
addressing_mode getOperandAddressingMode(char *operand);

/* Switch case that sends it to either processString() or processData()
 * param arguments - the lines content
*/
void processDeclarationLine(char *arguments);

/* Parses a .string declaration. Checks that the string is correct syntax wise. Adds the content a DeclarationCommands linked list
 * param arguments - the line content
*/
void processString(char *arguments);

/* Parses a .data declaration. Checks that the values are comma separated and valid. Adds the content a DeclarationCommands linked list
 * param arguments - the line content
*/
void processData(char *arguments);

/* Parses a .extern declaration. Adds / updates the label to LabelChart linked list if valid
 * param arguments - the line content
*/
void processExternLine(char *arguments);

/* Parses the instruction line. Gathers the information for the decode.c to write on the fly
 * param arguments - the line content
 * param filename - the name of the file without the suffix to send over to the decoder
*/
void processInstructionLine(char *arguments, char *filename);

/* Handles the destination and / or origin operands, gathers information to send to decode.c
 * param filename - the name of the file without the suffix to send over to the decoder
*/
void handleOperands(char *filename);

/* Assigns the relevant values to the Operand struct based on the operands that were checked in isValidOperand()
 * param operand - the Operand struct to manipulate
 * param reserve - reserve flag to assign for the Operand
 * param value - the value to assign for the Operand
*/
void assignOperandValues(Operand *operand, boolean reserve, char *value);

/* Assigns the relevant values to the Instruction struct based on the current instruction operation */
void assignInstructionValues();

/* Resets the values for all of the relevant variables for the first iteration */
void resetValues();

#endif /* FIRST_ITERATION_H */
