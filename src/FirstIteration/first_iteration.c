#include "first_iteration.h"
#include "../LabelChart/label_chart.h"

int IC = 100;
int DC = 0;
int line_counter;
boolean errors_exist = False;
boolean symbol_flag;
char label[MAX_LABEL_CHARS];
char *type = NULL;
const operation *commandPointer = NULL;
const regis *regisPointer = NULL;
const char delimiters[] = " \t\n";
Label *head = NULL;
void first_iteration(char * filename, FILE * file){
    head = NULL;
    int token_counter;
    line_counter = 0;
    char line[MAX_LINE_CHARS];
    char * token = NULL;
    errors_exist = False;
    while(fgets(line, sizeof(line), file)){
        symbol_flag = False;
        token_counter = 0;
        line_counter++;
        memset(label, 0, MAX_LABEL_CHARS);
        token = strtok(line, delimiters);
        while(token != NULL) {
/*
            printf("String: %s\t\tLine no.%d\t\tToken No.%d\n\n\n", token, line_counter, ++token_counter);
*/
            if (is_label(token, True)) {
                symbol_flag = True;
            }
            else if (is_comment(token)){
                while(strcmp(token, "\n") != 0){
                    *token++;
                }
                token = strtok(NULL, delimiters);
            }
            else if (is_data(token))
                is_extern() ? process_extern_line(line, token) : process_data_line(line, token, symbol_flag);
            else if (is_command(token))
                process_command_line(line, token, symbol_flag);
            token = strtok(NULL, delimiters);
        }
    }
    updateLabelChart(&head, IC);
    printLabelChart(&head);
}

boolean is_label(const char *token, boolean toCheckColon){
    size_t len = strlen(token);
    if (isalpha(token[0]) && (toCheckColon ? token[len - 1] == ':' : True)) {
        if (len >= MAX_LABEL_CHARS)
            errors_exist = errorReport(LABEL_TOO_LONG, line_counter, token);
        else if (!symbol_flag) {
            memcpy(label, token,  (toCheckColon ? len - 1 : len));
            label[len] = '\0';
            return True;
        }
        else
            errors_exist = errorReport(TOO_MANY_LABELS, line_counter, token);
    }
    return False;
}
boolean is_data(char token[]){
    size_t len = strlen(token);
    char * data_name;
    data_name = (char *) malloc(len - 1);
    strncpy(data_name, token + 1, len -1);
    data_name[len - 1] = '\0';
    if (token[0] == '.') {
        if (is_valid_data_name(data_name)) {
            /*free(data_name);*/
            return True;
        }
        else
            errors_exist = errorReport(UNKNOWN_DATA_COMMAND, line_counter, token);
    }
    /*free(data_name);*/
    return False;
}
boolean is_command(char * command_name){
    int i;
    for (i=0; i < OPERATION_NUM ; i++){
        if (strcmp(command_name, operations[i].name) == 0 ) {
            commandPointer = &operations[i];
            return True;
        }
    }
    errors_exist = errorReport(UNKNOWN_OPERATION_COMMAND, line_counter, command_name);
    return False;
}
boolean is_register(char * regis){
    int i;
    for (i=0 ; i<REGISTER_NUM ; i++){
        if (strcmp(regis, registers[i].name) == 0) {
            regisPointer = &registers[i];
            return True;
        }
    }
    return False;
}
boolean is_comment(const char token[]){
    if (token[0] == ';')
        return True;
    return False;
}
boolean is_extern(){
    boolean bool = strcmp(type, "extern") == 0 ?  True : False;
    return bool;
}
boolean is_valid_data_name(char * data_name){
    if (
        strcmp(data_name, "string") == 0 ||
        strcmp(data_name, "data") == 0 ||
        strcmp(data_name, "entry") == 0 ||
        strcmp(data_name, "extern") == 0
    ) {
        type = malloc(sizeof(data_name));
        strcpy(type, data_name);
        return True;
    }
    return False;
}
void process_data_line(const char * token, char * line, boolean isLabel){
    size_t len;
    int i = 0;
    char * stringContent;
    char * saveContent;
    if (strcmp(type, "string") == 0){
        if (isLabel && isUniqueLabel(&head, label))
            addToLabelChart(&head, label, DC, STRING, False, False);
        token = strtok(NULL, delimiters);
        if (token[0]=='"' && token[len = (strlen(token) - 1)]=='"') {
            stringContent = malloc(len);
            strncpy(stringContent, token + 1, len-1);
            stringContent[len - 1] = '\0';
            for (i ; i < strlen(stringContent) ; i++){
                printf("%d: %c\n", DC, stringContent[i]);
                DC++;
            }
            printf("%d: \\0\n", DC);
            DC++;
            /* Decode */
        } else {
            errors_exist = errorReport(NO_QUOTATIONS, line_counter, token);
        }
    } else { /* .data */
        if (isLabel && isUniqueLabel(&head, label))
            addToLabelChart(&head, label, DC, DATA, False, False);
        token = strtok(NULL, ",\n");
        while (token != NULL){
            saveContent = malloc(strlen(token));
            strcpy(saveContent, token);
            saveContent[strlen(saveContent)] = '\0';
            if (isValidNumber(saveContent)) {
                /* Decode */
                printf("%d: %d\n",DC ,atoi(saveContent));
                DC++;
            }
            token = strtok(NULL, ",\n");
        }
    }
    printf("SIZE OF DC: %d\n\n", DC);
}
void process_extern_line(const char token[], char * line){
    if (symbol_flag) {
        errors_exist = errorReport(EXTERN_AFTER_LABEL, line_counter, token);
        return;
    }
    token = strtok(NULL, delimiters);
    if (is_label(token, False))
        isUniqueLabel(&head, label) ? addToLabelChart(&head, label, 0, DATA, False, True) : updateLabelValue(&head, label, 0);
    else
        errors_exist = errorReport(NOT_VALID_LABEL, line_counter, token);

}
void process_command_line(char token[], char * line, boolean isLabel){
    if (isLabel && isUniqueLabel(&head, label))
        addToLabelChart(&head, label, IC, CODE, False, False);
    printf("IC: %d\n", IC);
    IC++;
    if (commandPointer -> operands > 0)
        is_valid_operand(token, commandPointer -> operands);

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
            errors_exist = errorReport(NOT_VALID_NUMBER, line_counter, number);
            return False;
        }
    }
    number = strpbrk(number, " ");
    if (number == NULL)
        return isValidParam;
    while (number[0] == ' ' || number[0] == '\t')
        *number++;
    if (strcmp(number, "") != 0) {
        errors_exist = errorReport(MISSING_COMMAS, line_counter, number);
        isValidParam = False;
    }
    return isValidParam;
}

boolean is_valid_operand(char * operand, int paramNum){
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
                errors_exist = errorReport(NOT_COMMA_SEPARATED, line_counter);
                return False;
            }
        }
        operandType = getOperandAddressingMode(operand);
        if (operandType != REGISTER)
            printf("Reserved address for operand %d\n", ++IC);
        if (!isValidAddressingMode(operandType, tokenCounter))
            errors_exist = errorReport(INVALID_OPERAND_TYPE, line_counter, operandType, commandPointer -> name);
        operand = strtok(NULL, ",\n");
        /* Decode the type  */
        if (tokenCounter > paramNum) {
            errors_exist = errorReport(TOO_MANY_ARGUMENTS, line_counter);
            return False;
        }
    }
    if (tokenCounter < paramNum) {
        errors_exist = errorReport(TOO_FEW_ARGUMENTS, line_counter);
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
    } else if (is_register(operand)) {
        return REGISTER;
    } else if (operand[0] == '&') {
        return INDIRECT;
    } else
        return DIRECT;
}