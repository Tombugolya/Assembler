#include "decode.h"

void decodeInstruction(InstructionData data, char *filename) {
    int num;
    char binary[25];
    char *ptr;
    binary[0] = '\0';
    printBin(data.opCode, 6, binary);
    printBin(data.originMode, 2, binary);
    printBin(data.regisOrigin, 3, binary);
    printBin(data.destMode, 2, binary);
    printBin(data.regisDest, 3, binary);
    printBin(data.function,5, binary);
    printBin(1, 1, binary);
    printBin(0, 1, binary);
    printBin(0, 1, binary);
    binary[24] = '\0';
    num=strtol(binary, &ptr, 2);
    printf("%s\n",binary);
    writeHexadecimal(num, data.address, filename);
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
        printBin(code.dataCode, 24, binary);
        binary[24] = '\0';
        num=strtol(binary, &ptr, 2);
        printf("%s\n",binary);
        fprintf(filePointer, "%08d\t%06x\n", current->address, num);
        current = current -> next;
        binary[0] = '\0';
    }
    fclose(filePointer);
}
/* TODO: Understand how to leave spot for the reserved..*/
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
