#include "decode.h"

void decodeInstruction(InstructionData data, char * filename) {
    InstructionCode instructionCode;
    instructionCode.opCode = data.opCode;
    instructionCode.originMode = data.originMode;
    instructionCode.regisOrigin = data.regisOrigin;
    instructionCode.destMode = data.destMode;
    instructionCode.regisDest = data.regisDest;
    instructionCode.function = data.function;
    instructionCode.absolute = 1;
    instructionCode.relocatable = 0;
    instructionCode.external = 0;
    writeHexadecimal(instructionCode, data.address, filename);

}

/* TODO: Implement also writing for this function to the file, it is executed at the end of the first iteration */
void decodeData(DataCommands ** list){
    DataCode code;
    DataCommands *current = *list;
    while (current != NULL){
        if (current -> type == STRING)
            code.dataCode = current -> character;
        else if (current -> type == NUMBER)
            code.dataCode = current -> num;
        current = current -> next;
    }
}
/* TODO: File writing should start from line 2, after first iteration line 1 should be reserved for IC : DC*/
/* TODO: Potentially I might want to not work with bitfields but rather with >> | & and such...*/
/* TODO: Understand how to leave spot for the reserved..*/
void writeHexadecimal(InstructionCode bitField, int address, char * name) {
    FILE *filePointer;
    char *fileName;
    fileName = malloc(strlen(name));
    strcpy(fileName, name);
    strcat(fileName, ".ob");
    filePointer = fopen(fileName, "w");
    fprintf(filePointer, "%d\t%x\n",
           address,
           bitField
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
