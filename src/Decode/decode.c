#include "decode.h"

void decodeInstruction(InstructionData data, char *filename) {
    int num;
    char binary[25];
    char *ptr;
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
    printf("%s\n",binary);
    writeHexadecimal(num, data.address, filename);
}
void writeOperand(char *value, char *name, int address) {
    FILE *filePointer;
    char *fileName;
    char *ptr;
    char binary[25];
    int num;
    fileName = malloc(strlen(name));
    strcpy(fileName, name);
    strcat(fileName, ".ob");
    filePointer = fopen(fileName, "a");
    binary[0] = '\0';
    num = strtol(value, &ptr, 10);
    appendToBinaryString(num, 21, binary);
    appendToBinaryString(1, 1, binary);
    appendToBinaryString(0, 1, binary);
    appendToBinaryString(0, 1, binary);
    binary[24] = '\0';
    num=strtol(binary, &ptr, 2);
    fprintf(filePointer, "%08d\t%06x\n", address, num);
    fclose(filePointer);
}

void reserveOperand(char *value, char *name, int address) {
    FILE *filePointer;
    char *fileName;
    fileName = malloc(strlen(name));
    strcpy(fileName, name);
    strcat(fileName, ".ob");
    filePointer = fopen(fileName, "a");
    fprintf(filePointer, "%d\t%s\n", address, value);
    fclose(filePointer);
}

void writeICDC(char *name, int IC, int DC){
    FILE *filePointer;
    char *fileName;
    fileName = malloc(strlen(name));
    strcpy(fileName, name);
    strcat(fileName, ".ob");
    filePointer = fopen(fileName, "r+");
    fprintf(filePointer,"%*d\t%*d\n", 8, IC, 6, DC);
    fclose(filePointer);
}

void writeData(DataCommands ** list, char *name){
    FILE *filePointer;
    DataCode code;
    DataCommands *current = *list;
    char *fileName;
    char *ptr;
    char binary[25];
    int num;
    binary[0] = '\0';
    fileName = malloc(strlen(name));
    strcpy(fileName, name);
    strcat(fileName, ".ob");
    filePointer = fopen(fileName, "a");
    while (current != NULL){
        if (current -> type == STRING)
            code.dataCode = current->character;
        else if (current -> type == NUMBER)
            code.dataCode = current->num;
        appendToBinaryString(code.dataCode, 24, binary);
        binary[24] = '\0';
        num=strtol(binary, &ptr, 2);
        printf("%s\n",binary);
        fprintf(filePointer, "%08d\t%06x\n", current->address, num);
        current = current -> next;
        binary[0] = '\0';
    }
    fclose(filePointer);
}

void writeHexadecimal(int num, int address, char * name) {
    FILE *filePointer;
    char *fileName;
    fileName = malloc(strlen(name));
    strcpy(fileName, name);
    strcat(fileName, ".ob");
    filePointer = fopen(fileName, "a");
    fprintf(filePointer, "%08d\t%06x\n",
           address,
           num
    );
    /*fprintf(filePointer, "%d\t%d\t%d\n%d\t%d\t%d\n%d\t%d\t%d\n%x\n\n",
            (int) bitField.opCode,
            (int) bitField.originMode,
            (int) bitField.regisOrigin,
            (int) bitField.destMode,
            (int) bitField.regisDest,
            (int) bitField.function,
            (int) bitField.absolute,
            (int) bitField.relocatable,
            (int) bitField.external,
            bitField
    );*/
    fclose(filePointer);
}
