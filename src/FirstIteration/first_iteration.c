#include "first_iteration.h"
/* TODO: add isEntry option to first iteration that will either add to label chart or enable isEntry on the label chart or skip in the first iteration */
const char delimiters[] = " \t\n";
static const InstructionData EmptyInstruction = {0, EMPTY, 0, 0, 0, 0, 0};
static const Operand EmptyOperand = {"\0", 0, 0, False, 0};
const Operation *commandPointer = NULL;
const Regis *regisPointer = NULL;
int IC;
int DC;
int lineCount;
char label[MAX_LABEL_CHARS];
char *type = NULL;
boolean errorsExist;
boolean isLabelFlag;
InstructionData instruction;
Label *labelHead = NULL;
DataCommands *dataHead = NULL;
Operand dest;
Operand origin;

void resetValues() {
    IC = 100;
    DC = 0;
    lineCount = 0;
    errorsExist = False;
    isLabelFlag = False;
    memset(label, 0, sizeof label);
    commandPointer = NULL;
    regisPointer = NULL;
    labelHead = NULL;
    dataHead = NULL;
}

void firstIteration(char * filename, FILE * file){
    char line[MAX_LINE_CHARS];
    char * token = NULL;
    resetValues();
    createObFile(filename);
    while(fgets(line, sizeof(line), file)){
        isLabelFlag = False;
        lineCount++;
        memset(label, 0, MAX_LABEL_CHARS);
        token = strtok(line, delimiters);
        while(token != NULL) {
            if (isLabel(token, True)) {
                isLabelFlag = True;
            }
            else if (isComment(token)){
                token = NULL;
                break;
            }
            else if (isData(token))
                isExtern() ? processExternLine(line) : processDataLine(line, isLabelFlag);
            else if (isInstruction(token))
                processInstructionLine(line, isLabelFlag, filename);
            token = strtok(NULL, delimiters);
        }
    }
    updateLabelChart(&labelHead, IC);
    /*printLabelChart(&labelHead);*/
    updateDataCommands(&dataHead, IC);
    /*printDataCommands(&dataHead);*/
    writeICDC(filename, IC-100, DC);
    writeData(&dataHead, filename);
    if (errorsExist)
        return;
}

void createObFile(char * name) {
    FILE * filePointer;
    char *fileName;
    fileName = malloc(strlen(name));
    strcpy(fileName, name);
    strcat(fileName, ".ob");
    filePointer = fopen(fileName, "w");
    fprintf(filePointer,"%*d\t%*d\n", 8, 10, 6, 10);
    fclose(filePointer);
}

void printInstruction(){
    printf("Address\topCode\tfunc\tdeMode\tregDest\torMode\tregOrigin\n");
    printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n", instruction.address,
           instruction.opCode, instruction.function,
           instruction.destMode, instruction.regisDest,
           instruction.originMode, instruction.regisOrigin);
}

boolean isLabel(const char *labelName, boolean toCheckColon){
    size_t len = strlen(labelName);
    if (isalpha(labelName[0]) && (toCheckColon ? labelName[len - 1] == ':' : True)) {
        if (len >= MAX_LABEL_CHARS)
            errorsExist = errorReport(LABEL_TOO_LONG, lineCount, labelName);
        else if (!isLabelFlag) {
            memcpy(label, labelName, (toCheckColon ? len - 1 : len));
            label[len] = '\0';
            return True;
        }
        else
            errorsExist = errorReport(TOO_MANY_LABELS, lineCount, labelName);
    }
    return False;
}

boolean isData(char dataName[]){
    size_t len = strlen(dataName);
    char * name;
    name = (char *) malloc(len - 1);
    strncpy(name, dataName + 1, len - 1);
    name[len - 1] = '\0';
    if (dataName[0] == '.') {
        if (isValidDataName(name))
            return True;
        else
            errorsExist = errorReport(UNKNOWN_DATA_COMMAND, lineCount, dataName);
    }
    return False;
}

boolean isInstruction(char * commandName){
    int i;
    for (i=0; i < OPERATION_NUM ; i++){
        if (strcmp(commandName, operations[i].name) == 0 ) {
            commandPointer = &operations[i];
            return True;
        }
    }
    errorsExist = errorReport(UNKNOWN_OPERATION_COMMAND, lineCount, commandName);
    return False;
}

boolean isRegister(char * regis){
    int i;
    for (i=0 ; i < REGISTER_NUM ; i++){
        if (strcmp(regis, registers[i].name) == 0) {
            regisPointer = &registers[i];
            return True;
        }
    }
    return False;
}

boolean isComment(const char commentSymbol[]){
    if (commentSymbol[0] == ';')
        return True;
    return False;
}

boolean isExtern(){
    boolean bool = strcmp(type, "extern") == 0 ?  True : False;
    return bool;
}

boolean isValidDataName(char * dataName){
    if (
        strcmp(dataName, "string") == 0 ||
        strcmp(dataName, "data") == 0 ||
        strcmp(dataName, "entry") == 0 ||
        strcmp(dataName, "extern") == 0
    ) {
        type = malloc(sizeof(dataName));
        strcpy(type, dataName);
        return True;
    }
    return False;
}

void processDataLine(char * arguments, boolean isLabel){
    size_t len;
    int i;
    int num;
    char * stringContent;
    char * saveContent;
    char * endPtr;
    if (strcmp(type, "string") == 0){
        if (isLabel && isUniqueLabel(&labelHead, label))
            addToLabelChart(&labelHead, label, DC, STRING, False, False);
        arguments = strtok(NULL, "\n");
        arguments = trimWhiteSpace(arguments);
        if (arguments[0] == '"' && arguments[len = (strlen(arguments) - 1)] == '"') {
            stringContent = malloc(len);
            strncpy(stringContent, arguments + 1, len - 1);
            stringContent[len - 1] = '\0';
            for (i=0 ; i < strlen(stringContent) ; i++){
                addToDataCommands(&dataHead, DC, STRING, stringContent[i]);
                DC++;
            }
            addToDataCommands(&dataHead, DC, STRING, '\0');
            DC++;
        } else {
            errorsExist = errorReport(NO_QUOTATIONS, lineCount, arguments);
        }
    } else if (strcmp(type, "data") == 0) {
        if (isLabel && isUniqueLabel(&labelHead, label))
            addToLabelChart(&labelHead, label, DC, NUMBER, False, False);
        arguments = strtok(NULL, ",\n");
        while (arguments != NULL){
            saveContent = malloc(strlen(arguments));
            strcpy(saveContent, arguments);
            saveContent[strlen(saveContent)] = '\0';
            if (isValidNumber(saveContent)) {
                /* Decode */
                num = strtol(saveContent, &endPtr, 10);
                addToDataCommands(&dataHead, DC, NUMBER, num);
                printf("%d: %d\n",DC ,num);
                DC++;
            }
            arguments = strtok(NULL, ",\n");
        }
    } else /* .entry */
        ;
}

void processExternLine(const char arguments[]){
    if (isLabelFlag) {
        errorsExist = errorReport(EXTERN_AFTER_LABEL, lineCount, arguments);
        return;
    }
    arguments = strtok(NULL, delimiters);
    if (isLabel(arguments, False))
        isUniqueLabel(&labelHead, label) ? addToLabelChart(&labelHead, label, 0, NUMBER, False, True) : updateLabelValue(&labelHead, label, 0);
    else
        errorsExist = errorReport(INVALID_LABEL, lineCount, arguments);

}

void processInstructionLine(char arguments[], boolean isLabel, char * filename){
    instruction = EmptyInstruction;
    dest = EmptyOperand;
    origin = EmptyOperand;
    if (isLabel && isUniqueLabel(&labelHead, label))
        addToLabelChart(&labelHead, label, IC, CODE, False, False);
    instruction.address = IC;
    instruction.opCode = commandPointer -> opCode;
    instruction.function = commandPointer -> function;
    IC++;
    if (commandPointer -> operands > 0) {
        if (isValidOperand(arguments, commandPointer->operands)) {
            printInstruction();
            decodeInstruction(instruction, filename);
            if (dest.address)
                dest.reserve ? reserveOperand(dest, filename) : writeOperand(dest, filename);
            if (origin.address)
                origin.reserve ? reserveOperand(origin, filename) : writeOperand(origin, filename);
        }
        else
            fprintf(stderr, "Errors returned in line %d\n", lineCount);
    }
    else { /* No operands */
        printInstruction();
        decodeInstruction(instruction, filename);
    }
}

/*TODO: Operand Struct should potentially have a 'Active' parameter too */
/*TODO: Potentially you might want to change all of the 'filename' parameters to be the file, instead of opening and closing it every function call*/
boolean isValidOperand(char * operand, int maxParamNum){
    int paramNum = 0;
    char *pt = NULL;
    addressing_mode operandType;
    Operand *pointer;
    operand = strtok(NULL, ",\n");
    while (operand != NULL) {
        paramNum++;
        if (paramNum > maxParamNum)
            return errorsExist = errorReport(TOO_MANY_ARGUMENTS, lineCount);
        operand = trimWhiteSpace(operand);
        pt = strpbrk(operand, " \t");
        if (pt != NULL)
            return errorsExist = errorReport(NOT_COMMA_SEPARATED, lineCount);
        operandType = getOperandAddressingMode(operand);
        if (!isValidAddressingMode(operandType, paramNum))
            return errorsExist = errorReport(INVALID_OPERAND_TYPE, lineCount, operandType, commandPointer->name);
        if (FIRST_PARAM) pointer = &dest;
        if (SECOND_PARAM) pointer = &origin;
        switch (operandType){
            case IMMEDIATE:
                operand++;
                (*pointer).value = operand;
                (*pointer).reserve = False;
                (*pointer).address = IC++;
                (*pointer).mode = operandType;
                printf("INFO: str %s\tres %d\tadd %d\tmode %d\n", pointer->value, pointer->reserve, pointer->address, pointer->mode);
                break;
            case INDIRECT:
            case DIRECT:
                (*pointer).value = operand;
                (*pointer).reserve = True;
                (*pointer).address = IC++;
                (*pointer).mode = operandType;
                printf("INFO: str %s\tres %d\tadd %d\tmode %d\n", pointer->value, pointer->reserve, pointer->address, pointer->mode);
                break;
            case REGISTER:
                if (FIRST_PARAM) instruction.regisDest = regisPointer->value;
                if (SECOND_PARAM) instruction.regisOrigin = regisPointer->value;
                (*pointer).reserve = False;
                break;
            default:
                return False;
        }
        operand = strtok(NULL, ",\n");
    }
    if (paramNum < maxParamNum) {
        errorsExist = errorReport(TOO_FEW_ARGUMENTS, lineCount);
        return False;
    }
    return True;
}

boolean isValidNumber(char * number){
    int i;
    boolean isValidParam = True;
    number = trimWhiteSpace(number);
    for(i=0; i < strlen(number) ; i++) {
        if (i==0 && (number[i] == '-' || number[i] == '+'))
            isValidParam = True;
        else if (number[i] != ' ' && number[i] != '\t' && !isdigit(number[i])) {
            errorsExist = errorReport(INVALID_NUMBER, lineCount, number);
            return False;
        }
    }
    return isValidParam;
}

boolean isValidAddressingMode(addressing_mode mode, int operandNum){
    int i;
    const addressing_mode *modes = NULL;
    if (operandNum == 1)
        modes = commandPointer->modesDest;
    else if (operandNum == 2)
        modes = commandPointer->modesOrigin;
    for (i = 0; i < MAX_APPLICABLE_MODES; i++) {
        if (mode == modes[i]) {
            if (operandNum == 1) {
                instruction.destMode = modes[i];
            }
            else if (operandNum == 2) {
                instruction.originMode = modes[i];
            }
            return True;
        }
    }
    return False;
}

addressing_mode getOperandAddressingMode(char * operand) {
    operand = trimWhiteSpace(operand);
    if (operand[0] == '#'){
        if (isdigit(operand[1]) || operand[1] == '-' || operand[1] == '+' ) {
            operand++;
            if (isValidNumber(operand))
                return IMMEDIATE;
        }
        errorsExist = errorReport(EMPTY_NUMBER, lineCount);
    } else if (isRegister(operand)) {
        return REGISTER;
    } else if (operand[0] == '&') {
        operand++;
        if (isLabel(operand, False))
            return INDIRECT;
    } else if (isLabel(operand, False))
        return DIRECT;
    errorsExist = errorReport(INVALID_MODE, lineCount, operand);
    return end;
}
