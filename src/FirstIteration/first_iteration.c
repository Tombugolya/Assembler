#include "first_iteration.h"
#include "../LabelChart/label_chart.h"
#include "../LinkedListOfDataCommands/data_commands.h"
/* TODO: Add DCData linked list that will contain all of the data. IC you can decode in real time and DC afterwards with the linked list */
/* TODO: add isEntry option to first iteration that will either add to label chart or enable isEntry on the label chart or skip in the first iteration */
int IC;
int DC;
int lineCount;
boolean errorsExist;
boolean isLabelFlag;
char label[MAX_LABEL_CHARS];
char *type = NULL;
const Operation *commandPointer = NULL;
const Regis *regisPointer = NULL;
const char delimiters[] = " \t\n";
Label *labelHead = NULL;
DataCommands *dataHead = NULL;
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
    int token_counter;
    resetValues();

    while(fgets(line, sizeof(line), file)){
        isLabelFlag = False;
        token_counter = 0;
        lineCount++;
        memset(label, 0, MAX_LABEL_CHARS);
        token = strtok(line, delimiters);
        while(token != NULL) {
/*
            printf("String: %s\t\tLine no.%d\t\tToken No.%d\n\n\n", token, line_counter, ++token_counter);
*/
            if (isLabel(token, True)) {
                isLabelFlag = True;
            }
            else if (isComment(token)){
                while(strcmp(token, "\n") != 0){
                    *token++;
                }
                token = strtok(NULL, delimiters);
            }
            else if (isData(token))
                isExtern() ? processExternLine(line, token) : processDataLine(line, token, isLabelFlag);
            else if (isInstruction(token))
                processInstructionLine(line, token, isLabelFlag);
            token = strtok(NULL, delimiters);
        }
    }
    updateLabelChart(&labelHead, IC);
    printLabelChart(&labelHead);
    if (errorsExist)
        exit(1);
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
        if (isValidDataName(name)) {
            /*free(name);*/
            return True;
        }
        else
            errorsExist = errorReport(UNKNOWN_DATA_COMMAND, lineCount, dataName);
    }
    /*free(name);*/
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
    for (i=0 ; i<REGISTER_NUM ; i++){
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
void processDataLine(const char * arguments, char * line, boolean isLabel){
    size_t len;
    int i = 0;
    int num;
    char * stringContent;
    char * saveContent;
    if (strcmp(type, "string") == 0){
        if (isLabel && isUniqueLabel(&labelHead, label))
            addToLabelChart(&labelHead, label, DC, STRING, False, False);
        arguments = strtok(NULL, delimiters);
        if (arguments[0] == '"' && arguments[len = (strlen(arguments) - 1)] == '"') {
            stringContent = malloc(len);
            strncpy(stringContent, arguments + 1, len - 1);
            stringContent[len - 1] = '\0';
            for (i ; i < strlen(stringContent) ; i++){
                addToDataCommands(&dataHead, DC, STRING, stringContent[i]);
                printf("%d: %c\n", DC, stringContent[i]);
                DC++;
            }
            addToDataCommands(&dataHead, DC, STRING, '\0');
            printf("%d: \\0\n", DC);
            DC++;
            /* Decode */
        } else {
            errorsExist = errorReport(NO_QUOTATIONS, lineCount, arguments);
        }
    } else { /* .data */
        if (isLabel && isUniqueLabel(&labelHead, label))
            addToLabelChart(&labelHead, label, DC, DATA, False, False);
        arguments = strtok(NULL, ",\n");
        while (arguments != NULL){
            saveContent = malloc(strlen(arguments));
            strcpy(saveContent, arguments);
            saveContent[strlen(saveContent)] = '\0';
            if (isValidNumber(saveContent)) {
                /* Decode */
                num = atoi(saveContent);
                addToDataCommands(&dataHead, DC, DATA, num);
                printf("%d: %d\n",DC ,num);
                DC++;
            }
            arguments = strtok(NULL, ",\n");
        }
    }
    printf("SIZE OF DC: %d\n\n", DC);
}
void processExternLine(const char arguments[], char * line){
    if (isLabelFlag) {
        errorsExist = errorReport(EXTERN_AFTER_LABEL, lineCount, arguments);
        return;
    }
    arguments = strtok(NULL, delimiters);
    if (isLabel(arguments, False))
        isUniqueLabel(&labelHead, label) ? addToLabelChart(&labelHead, label, 0, DATA, False, True) : updateLabelValue(&labelHead, label, 0);
    else
        errorsExist = errorReport(INVALID_LABEL, lineCount, arguments);

}
void processInstructionLine(char arguments[], char * line, boolean isLabel){
    if (isLabel && isUniqueLabel(&labelHead, label))
        addToLabelChart(&labelHead, label, IC, CODE, False, False);
    printf("IC: %d\n", IC);
    IC++;
    if (commandPointer -> operands > 0)
        isValidOperand(arguments, commandPointer -> operands);

}

boolean isValidNumber(char * number){
    int i=0;
    boolean isValidParam = True;
    while (number[0] == ' ' || number[0] == '\t')
        *number++;
    for(i ; i < strlen(number) ; i++) {
        if (i==0 && number[i] == '-')
            isValidParam = True;
        else if (number[i] != ' ' && number[i] != '\t' && !isdigit(number[i])) {
            errorsExist = errorReport(INVALID_NUMBER, lineCount, number);
            return False;
        }
    }
    number = strpbrk(number, " ");
    if (number == NULL)
        return isValidParam;
    while (number[0] == ' ' || number[0] == '\t')
        *number++;
    if (strcmp(number, "") != 0) {
        errorsExist = errorReport(MISSING_COMMAS, lineCount, number);
        isValidParam = False;
    }
    return isValidParam;
}

boolean isValidOperand(char * operand, int maxParamNum){
    int i=0;
    int tokenCounter = 0;
    char * pt = NULL;
    boolean isValidParam = True;
    int operandType;
    while (operand[0] == ' ' || operand[0] == '\t')
        *operand++;
    operand = strtok(NULL, ",\n");
    while (operand != NULL) {
        tokenCounter++;
        while (operand[0] == ' ' || operand[0] == '\t')
            *operand++;
        pt = strpbrk(operand, " \t");
        if (pt != NULL) {
            while (pt[0] == ' ' || pt[0] == '\t')
                *pt++;
            if (strcmp(pt, "") != 0) {
                errorsExist = errorReport(NOT_COMMA_SEPARATED, lineCount);
                return False;
            }
        }
        operandType = getOperandAddressingMode(operand);
        if (operandType != REGISTER)
            printf("Reserved address for operand %d\n", IC++);
        if (!isValidAddressingMode(operandType, tokenCounter))
            errorsExist = errorReport(INVALID_OPERAND_TYPE, lineCount, operandType, commandPointer -> name);
        operand = strtok(NULL, ",\n");
        /* Decode the type  */
        if (tokenCounter > maxParamNum) {
            errorsExist = errorReport(TOO_MANY_ARGUMENTS, lineCount);
            return False;
        }
    }
    if (tokenCounter < maxParamNum) {
        errorsExist = errorReport(TOO_FEW_ARGUMENTS, lineCount);
        return False;
    }
    return True;
}
boolean isValidAddressingMode(addressing_mode mode, int operandNum){
    int i;
    const addressing_mode * modes;
    if (operandNum == 1)
        modes = commandPointer->modesDest;
    else if (operandNum == 2)
        modes = commandPointer->modesOrigin;
    for (i = 0; i < MAX_APPLICABLE_MODES; i++) {
        if (mode == modes[i]) return True;
    }
    return False;
}
addressing_mode getOperandAddressingMode(char * operand) {
    if (operand[0] == '#'){
        *operand++;
        if (isValidNumber(operand))
            return IMMEDIATE;
        return end;
    } else if (isRegister(operand)) {
        return REGISTER;
    } else if (operand[0] == '&') {
        return INDIRECT;
    } else
        return DIRECT;
}
