#ifndef ASSEMBLER_DECLARATION_COMMANDS_H
#define ASSEMBLER_DECLARATION_COMMANDS_H
#include "../Common/common.h"

/* DeclarationCommands linked list for all of the .string and .data declarations.
 * Used for writing the Declarations to the .test file AFTER having a clear IC.
 * This linked list collects all of the needed information for it to be sent to the decoder in bulk after decoding the instructions in First iteration.
 * param address - the memory address the declaration needs to be written to
 * param value - the value that will later be written to the file
 * param line_type - the type of declaration it is (STRING / DATA)
 * param next - the next node int the DeclarationCommands list
*/
typedef struct DeclarationCommands {
    int address;
    int value;
    line_type type;
    struct DeclarationCommands* next;
} DeclarationCommands;

/* Adds a new node to a DeclarationCommands head
 * param list - the head of the linked list
 * param address - the address to store
 * param type - the type to store
 * param value - the value to store
*/
void addToDeclarationCommands(DeclarationCommands **list, int address, line_type type, int value);

/* Updates the addresses for the declaration commands after the finalized IC value is returned.
 * This IC value is returned after all of the instruction line have been processes.
 * The initial value for each Declaration command will be increased by this IC value.
 * param list - the head of the linked list
 * param IC - the value to increment the addresses with
*/
void updateDeclarationCommandsAddresses(DeclarationCommands **list, int IC);

/* Frees the memory allocated for the DeclarationCommands
 * param list - the head of the linked list
*/
void freeDeclarationCommands(DeclarationCommands *list);

#endif