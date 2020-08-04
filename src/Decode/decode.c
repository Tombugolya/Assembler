#include "decode.h"

void decodeInstruction(InstructionData data, char *filename) {
    int num;
    char binary[25];
    char *ptr = NULL;
    binary[0] = '\0';
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
    num=strtol(binary, &ptr, 2);
    printf("%d\t%s\n",data.address, binary);
    writeHexadecimal(num, data.address, filename);
}

void writeOperand(Operand operand, char *name) {
    FILE *filePointer;
    char *fileName;
    char *ptr;
    char binary[25];
    int num;
    fileName = malloc(strlen(name));
    strcpy(fileName, name);
    strcat(fileName, ".test");
    filePointer = fopen(fileName, "a");
    binary[0] = '\0';
    num = strtol(operand.value, &ptr, 10);
    appendToBinaryString(num, 21, binary);
    appendToBinaryString(1, 1, binary);
    appendToBinaryString(0, 1, binary);
    appendToBinaryString(0, 1, binary);
    binary[24] = '\0';
    num=strtol(binary, &ptr, 2);
    fprintf(filePointer, "%08d\t%06x\n", operand.address, num);
    fclose(filePointer);
}

void writeDistance(FILE *file, int addressOrigin, int addressDestination) {
    int distance = addressOrigin - addressDestination;
    int num;
    char binary[25];
    char *ptr;
    binary[0] = '\0';
    appendToBinaryString(distance, 21, binary);
    appendToBinaryString(0, 1, binary);
    appendToBinaryString(1, 1, binary);
    appendToBinaryString(0, 1, binary);
    binary[24] = '\0';
    printf("BINARY DISTANCE: %s\n", binary);
    num = strtol(binary, &ptr, 2);
    fprintf(file, "%08d\t%06x\n", addressOrigin, num);
}

void writeExternal(FILE *file, int addressOrigin) {
    fprintf(file, "%08d\t%06x\n", addressOrigin, 1);
}

void writeAddress(FILE *file, int addressOrigin, int labelAddress) {
    int num;
    char binary[25];
    char *ptr;
    binary[0] = '\0';
    appendToBinaryString(labelAddress, 21, binary);
    appendToBinaryString(0, 1, binary);
    appendToBinaryString(1, 1, binary);
    appendToBinaryString(0, 1, binary);
    binary[24] = '\0';
    num = strtol(binary, &ptr, 2);
    fprintf(file, "%08d\t%06x\n", addressOrigin, num);
}

void reserveOperand(Operand operand, char *name) {
    FILE *filePointer;
    char *fileName;
    fileName = malloc(strlen(name));
    strcpy(fileName, name);
    strcat(fileName, ".test");
    filePointer = fopen(fileName, "a");
    printf("%c%d\t%s\n", RESERVED_SIGN, operand.address, operand.value);
    fprintf(filePointer, "%c%d\t%s\n", RESERVED_SIGN, operand.address, operand.value);
    fclose(filePointer);
}

void writeICDC(char *name, int IC, int DC){
    FILE *filePointer;
    char *fileName;
    fileName = malloc(strlen(name));
    strcpy(fileName, name);
    strcat(fileName, ".test");
    filePointer = fopen(fileName, "r+");
    fprintf(filePointer,"%*d\t%*d\n", 8, IC, 6, DC);
    fclose(filePointer);
}

void writeData(DeclarationCommands **list, char *name){
    FILE *filePointer;
    DataCode code;
    DeclarationCommands *current = *list;
    char *fileName;
    char *ptr;
    char binary[25];
    int num;
    binary[0] = '\0';
    fileName = malloc(strlen(name));
    strcpy(fileName, name);
    strcat(fileName, ".test");
    filePointer = fopen(fileName, "a");
    while (current != NULL){
        if (current -> type == STRING)
            code.dataCode = current -> character;
        else if (current -> type == DATA)
            code.dataCode = current -> num;
        appendToBinaryString(code.dataCode, 24, binary);
        binary[24] = '\0';
        num=strtol(binary, &ptr, 2);
        printf("%d\t%s\n",current -> address, binary);
        fprintf(filePointer, "%08d\t%06x\n", current -> address, num);
        current = current -> next;
        binary[0] = '\0';
    }
    fclose(filePointer);
}

void writeHexadecimal(int num, int address, char *name) {
    FILE *filePointer;
    char *fileName;
    fileName = malloc(strlen(name));
    strcpy(fileName, name);
    strcat(fileName, ".test");
    filePointer = fopen(fileName, "a");
    fprintf(filePointer, "%08d\t%06x\n",
           address,
           num
    );
    fclose(filePointer);
}

void writeToExtFile(char *filename, char *labelName, int address) {
    FILE *filePointer;
    char *fileName;
    fileName = malloc(strlen(filename));
    strcpy(fileName, filename);
    strcat(fileName, ".ext");
    filePointer = fopen(fileName, "a");
    fprintf(filePointer, "%s\t%08d\n",
            labelName,
            address
    );
    fclose(filePointer);
}

void writeToEntFile(char *filename, char *labelName, int address) {
    FILE *filePointer;
    char *fileName;
    fileName = malloc(strlen(filename));
    strcpy(fileName, filename);
    strcat(fileName, ".ent");
    filePointer = fopen(fileName, "a");
    fprintf(filePointer, "%s\t%08d\n",
            labelName,
            address
    );
    fclose(filePointer);
}