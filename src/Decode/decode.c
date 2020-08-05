#include "decode.h"

void decodeInstruction(InstructionData data, char *filename) {
    int num;
    char binary[25] = "";
    char *endPtr = NULL;
    appendToBinaryString(data.opCode, 6, binary);
    appendToBinaryString(data.originMode, 2, binary);
    appendToBinaryString(data.regisOrigin, 3, binary);
    appendToBinaryString(data.destMode, 2, binary);
    appendToBinaryString(data.regisDest, 3, binary);
    appendToBinaryString(data.function,5, binary);
    appendToBinaryString(1, 1, binary);
    appendToBinaryString(0, 1, binary);
    appendToBinaryString(0, 1, binary);
    binary[24] = '\0';
    num=strtol(binary, &endPtr, 2);
    writeHexadecimal(num, data.address, filename);
}

void writeOperand(Operand operand, char *name) {
    FILE *filePointer;
    char *fileName = concat(name, TEST_EXTENSION);
    char *endPtr;
    char binary[25] = "";
    int num;
    filePointer = fopen(fileName, "a");
    num = strtol(operand.value, &endPtr, 10);
    appendToBinaryString(num, 21, binary);
    appendToBinaryString(1, 1, binary);
    appendToBinaryString(0, 1, binary);
    appendToBinaryString(0, 1, binary);
    binary[24] = '\0';
    num = strtol(binary, &endPtr, 2);
    fprintf(filePointer, "%08d\t%06X\n", operand.address, num);
    fclose(filePointer);
    free(fileName);
}

void writeDistance(FILE *file, int addressOrigin, int addressDestination) {
    int distance = addressDestination - (addressOrigin - 1);
    int num;
    char binary[25] = "";
    char *endPtr;
    appendToBinaryString(distance, 21, binary);
    appendToBinaryString(1, 1, binary);
    appendToBinaryString(0, 1, binary);
    appendToBinaryString(0, 1, binary);
    binary[24] = '\0';
    num = strtol(binary, &endPtr, 2);
    fprintf(file, "%08d\t%06X\n", addressOrigin, num);
}

void writeExternal(FILE *file, int addressOrigin) {
    fprintf(file, "%08d\t%06X\n", addressOrigin, 1);
}

void writeAddress(FILE *file, int addressOrigin, int labelAddress) {
    int num;
    char binary[25] = "";
    char *endPtr;
    appendToBinaryString(labelAddress, 21, binary);
    appendToBinaryString(0, 1, binary);
    appendToBinaryString(1, 1, binary);
    appendToBinaryString(0, 1, binary);
    binary[24] = '\0';
    num = strtol(binary, &endPtr, 2);
    fprintf(file, "%08d\t%06X\n", addressOrigin, num);
}

void reserveOperand(Operand operand, char *name) {
    FILE *filePointer;
    char *fileName = concat(name, TEST_EXTENSION);
    filePointer = fopen(fileName, "a");
    fprintf(filePointer, "%c%d\t%s\n", RESERVED_SIGN, operand.address, operand.value);
    fclose(filePointer);
    free(fileName);
}

void writeICDC(char *name, int IC, int DC){
    FILE *filePointer;
    char *fileName = concat(name, TEST_EXTENSION);
    filePointer = fopen(fileName, "r+");
    fprintf(filePointer,"%*d\t%*d\n", 8, IC, 6, DC);
    fclose(filePointer);
    free(fileName);
}

void writeData(DeclarationCommands **list, char *name){
    FILE *filePointer;
    DeclarationCommands *current = *list;
    char *fileName = concat(name, TEST_EXTENSION);
    char *endPtr;
    char binary[25] = "";
    int num;
    filePointer = fopen(fileName, "a");

    while (current != NULL){
        appendToBinaryString(current -> value, 24, binary);
        binary[24] = '\0';
        num = strtol(binary, &endPtr, 2);
        fprintf(filePointer, "%08d\t%06X\n", current -> address, num);
        current = current -> next;
        binary[0] = '\0';
    }
    fclose(filePointer);
    free(fileName);
    freeDeclarationCommands(*list);
}

void writeHexadecimal(int num, int address, char *name) {
    FILE *filePointer;
    char *fileName = concat(name, TEST_EXTENSION);
    filePointer = fopen(fileName, "a");
    fprintf(filePointer, "%08d\t%06X\n",
       address,
       num
    );
    fclose(filePointer);
    free(fileName);
}

void writeToExtFile(char *filename, char *labelName, int address) {
    FILE *filePointer;
    char *fileName = concat(filename, EXT_EXTENSION);
    filePointer = fopen(fileName, "a");
    fprintf(filePointer, "%s\t%08d\n",
        labelName,
        address
    );
    fclose(filePointer);
    free(fileName);
}

void writeToEntFile(char *filename, LabelChart **list) {
    FILE *filePointer;
    LabelChart *current = *list;
    char *fileName = concat(filename, ENT_EXTENSION);
    boolean isPrinted = False;
    filePointer = fopen(fileName, "a");
    while (current != NULL) {
        if (current -> entry) {
            fprintf(filePointer, "%s\t%08d\n",
                current -> labelName,
                current -> address
            );
            isPrinted = True;
        }
        current = current -> next;
    }
    fclose(filePointer);
    if (!isPrinted)
        remove(fileName);
    free(fileName);
}