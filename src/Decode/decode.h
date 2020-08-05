#ifndef ASSEMBLER_DECODE_H
#define ASSEMBLER_DECODE_H
#include <stdarg.h>
#include "../LinkedListOfDataCommands/declaration_commands.h"
#include "../LabelChart/label_chart.h"
#include "../UtilFunctions/functions.h"

/* Decodes an InstructionData struct to the proper binary form and writes it to a .test file
 * param data - the InstructionData struct with all of the relevant fields filled out
 * param name - the name of the file to append to
*/
void writeInstruction(InstructionData data, char *name);

/* Decodes an Operand struct and writes it to the .test file
 * param operand - the operand struct with all of the relevant fields filled out
 * param name - the name of the file to append to
 * */
void writeOperand(Operand operand, char *name);

/* Decodes an Operand with a .reserve flag and writes placeholder text in the .test file.
 * This will later be parsed by the second iteration and will be completed in the .ob file.
 * param operand - a filled out operand struct to decode
 * param name - the name of the file to append to
*/
void reserveOperand(Operand operand, char *name);

/* Calculates the difference between the label address (destination) to where the current command is (origin).
 * Writes this value to the param file (an .ob file since this is related to the second iteration).
 * This function is for INDIRECT addressing mode operands.
 * param file - the file to write to
 * param addressOrigin - the address of the reserved line
 * param addressDestination - the address of the referenced label (&LABEL) we would want to know the distance from
*/
void writeDistance(FILE *file, int addressOrigin, int addressDestination);

/* Writes a value 1 in binary to an .ext file with the given address
 * param file - the .ext file
 * param address - the address to fill out
*/
void writeExternal(FILE *file, int address);

/* Writes the labels address and the reserved address in the .ob file
 * param file - the file to write to
 * param addressOrigin - the address of the reserved line
 * param labelAddress - the address of the label -- which is where the label was initialized
*/
void writeLabelAddress(FILE *file, int addressOrigin, int labelAddress);

/* Writes the first line of the .test (and later .ob) file.
 * The first line consists of the number of instructions \tab number of declarations found in the user inputted file.
 * param name - the name of the file
 * param IC - the number of instruction lines found
 * param DC - the number of declaration lines found
*/
void writeICDC(char *name, int IC, int DC);

/* Decodes the DeclarationCommands linked list and writes them in the .test file.
 * param list - a DeclarationCommands list with all of the relevant declarations found from the first iteration
 * param name - the name of the file
*/
void writeDeclarations(DeclarationCommands **list, char *name);

/* Creates an .ext file and writes every instance where an .extern'ed label chart was mentioned as an instruction operand.
 * The content that is written to this file is the NAME of the label \tab address where the label was mentioned.
 * param filename - the name of the file
 * param labelName - the name of the label
 * param address - the address from the reserved line where the .extern'ed label was mentioned
*/
void writeToExtFile(char *filename, char *labelName, int address);

/* Creates an .ent file and writes every label that was .entry'd and the address where it was initialized.
 * The function goes through all of the label chart and checks for .entry'd labels.
 * The content that is written to this file is the NAME of the label \tab address where the label was initialized.
 * param filename - the name of the file
 * param list - the label chart to iterate over
*/
void writeToEntFile(char *filename, LabelChart **list);

#endif //ASSEMBLER_DECODE_H
