#include "decode.h"

/* The general decoding and writing method goes like this:
 * 1) Create an empty string array with the length of the memory slot + 1 for null terminator (in our case it's 24 + 1)
 * 2) Apply appendToBinaryString in the correct order from left to right, specifying the number of bits for each section in second parameter
 * 3) Null terminate the string
 * 4) Use strtol() with a binary setting as the third parameter to convert to a decimal int
 * 5) Print to the file with %X so that the hexadecimal value will be printed instead of the decimal one
*/
void writeInstruction(InstructionData data, char *name) {
    int num;
    char binary[NUMBER_OF_BITS] = "";
    char *endPtr = NULL;
    FILE *filePointer;
    char *fileName = concat(name, TEST_EXTENSION);
    appendToBinaryString(data.opCode, 6, binary);       /* 6 bits for opcode */
    appendToBinaryString(data.originMode, 2, binary);   /* 2 bits for origin operand addressing mode */
    appendToBinaryString(data.regisOrigin, 3, binary);  /* 3 bits for origin operand register number */
    appendToBinaryString(data.destMode, 2, binary);     /* 2 bits for destination operand addressing mode*/
    appendToBinaryString(data.regisDest, 3, binary);    /* 3 bits for destination operand register number */
    appendToBinaryString(data.function,5, binary);      /* 5 bits for function code*/
    appendARE(1, 0, 0, binary);     /* 3 last bits for one of the ARE values */
    binary[NUMBER_OF_BITS - 1] = '\0';
    num = strtol(binary, &endPtr, 2);
    filePointer = fopen(fileName, "a");
    fprintf(filePointer, "%08d\t%06X\n", data.address, num);
    fclose(filePointer);
    free(fileName);
}

void writeOperand(Operand operand, char *name) {
    FILE *filePointer;
    char *fileName = concat(name, TEST_EXTENSION);
    char *endPtr;
    char binary[NUMBER_OF_BITS] = "";
    int num;
    filePointer = fopen(fileName, "a");
    num = strtol(operand.value, &endPtr, 10);       /* Converting char to int with strtol() */
    appendToBinaryString(num, 21, binary);            /* 21 bits for the operand value */
    appendARE(1, 0, 0, binary);   /* 3 bits for one of the ARE values */
    binary[NUMBER_OF_BITS - 1] = '\0';
    num = strtol(binary, &endPtr, 2);
    fprintf(filePointer, "%08d\t%06X\n", operand.address, num);
    fclose(filePointer);
    free(fileName);
}

void reserveOperand(Operand operand, char *name) {
    FILE *filePointer;
    char *fileName = concat(name, TEST_EXTENSION);
    filePointer = fopen(fileName, "a");
    fprintf(filePointer, "%c%d\t%s\n", RESERVED_SIGN, operand.address, operand.value);
    fclose(filePointer);
    free(fileName);
}

void writeDistance(FILE *file, int addressOrigin, int addressDestination) {
    int distance = addressDestination - (addressOrigin - 1);
    int num;
    char binary[NUMBER_OF_BITS] = "";
    char *endPtr;
    appendToBinaryString(distance, 21, binary);         /* 21 bits for the distance between label address and origin instruction value */
    appendARE(1, 0, 0, binary);     /* 3 bits for one of the ARE values */
    binary[NUMBER_OF_BITS - 1] = '\0';
    num = strtol(binary, &endPtr, 2);
    fprintf(file, "%08d\t%06X\n", addressOrigin, num);
}

void writeExternal(FILE *file, int addressOrigin) {
    fprintf(file, "%08d\t%06X\n", addressOrigin, 1); /* All external labels have the same '1' address so we just print the value 1 in base16 */
}

void writeLabelAddress(FILE *file, int addressOrigin, int labelAddress) {
    int num;
    char binary[NUMBER_OF_BITS] = "";
    char *endPtr;
    appendToBinaryString(labelAddress, 21, binary);     /* 21 bits for label address where the label was initialized */
    appendARE(0, 1, 0, binary);     /* 3 bits for one of the ARE values */
    binary[NUMBER_OF_BITS - 1] = '\0';
    num = strtol(binary, &endPtr, 2);
    fprintf(file, "%08d\t%06X\n", addressOrigin, num);
}

void writeICDC(char *name, int IC, int DC){
    FILE *filePointer;
    char *fileName = concat(name, TEST_EXTENSION);
    filePointer = fopen(fileName, "r+");
    fprintf(filePointer,"%*d\t%*d\n", 8, IC, 6, DC); /* If the .as file is empty - a file will be created with 0 & 0 as IC and DC */
    fclose(filePointer);
    free(fileName);
}

void writeDeclarations(DeclarationCommands **list, char *name){
    FILE *filePointer;
    DeclarationCommands *current = *list;
    char *fileName = concat(name, TEST_EXTENSION);
    char *endPtr;
    char binary[NUMBER_OF_BITS] = "";
    int num;
    filePointer = fopen(fileName, "a");

    while (current != NULL){
        appendToBinaryString(current -> value, 24, binary); /* A declaration argument uses all of the 24 bits */
        binary[NUMBER_OF_BITS - 1] = '\0';
        num = strtol(binary, &endPtr, 2);
        fprintf(filePointer, "%08d\t%06X\n", current -> address, num);
        current = current -> next;
        binary[0] = '\0';
    }
    fclose(filePointer);
    free(fileName);
    freeDeclarationCommands(*list);
}

void writeToExtFile(char *filename, char *labelName, int address) {
    FILE *filePointer;
    char *fileName = concat(filename, EXT_EXTENSION);
    filePointer = fopen(fileName, "a");
    fprintf(filePointer, "%s\t%08d\n", labelName, address);
    fclose(filePointer);
    free(fileName);
}

void writeToEntFile(char *filename, LabelChart **list) {
    FILE *filePointer;
    LabelChart *current = *list;
    char *fileName = concat(filename, ENT_EXTENSION);
    boolean isPrinted = False;
    filePointer = fopen(fileName, "a");

    while (current != NULL) { /* Iterating over a give label chart and printing for every label with an entry flag*/
        if (current -> entry) {
            fprintf(filePointer, "%s\t%08d\n", current -> labelName, current -> address);
            isPrinted = True;
        }
        current = current -> next;
    }
    fclose(filePointer);
    if (!isPrinted)
        remove(fileName);
    free(fileName);
}

void appendARE(int absolute, int relocatable, int external, char *binary) {
    appendToBinaryString(absolute, 1, binary);
    appendToBinaryString(relocatable, 1, binary);
    appendToBinaryString(external, 1, binary);
}