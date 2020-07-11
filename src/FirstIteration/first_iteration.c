#include "first_iteration.h"
#include "../LabelChart/label_chart.h"

int IC = 100;
int DC = 0;
boolean errors_exist = False;
boolean symbol_flag;
char label[MAX_LABEL_CHARS];
char * type;
char * command;
const char delimiters[] = " \t\n";
void first_iteration(char * filename, FILE * file){
    int line_counter = 0;
    int token_counter;
    char line[MAX_LINE_CHARS];
    char * token;
    errors_exist = False;
    while(fgets(line, sizeof(line), file)){
        symbol_flag = False;
        token_counter = 0;
        line_counter++;
        memset(label, 0, MAX_LABEL_CHARS);
        /*free(type);*/
        token = strtok(line, delimiters);
        while(token != NULL) {
/*
            printf("String: %s\t\tLine no.%d\t\tToken No.%d\n", token, line_counter, ++token_counter);
*/
            if (is_label(token)) {
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
}

boolean is_label(const char *token){
    size_t len = strlen(token);
    if (isalpha(token[0]) && token[len - 1] == ':' ) {
        if (len >= MAX_LABEL_CHARS) {
            fprintf(stderr, "Error: Label name \"%s\" is too long, up to %d characters are allowed\n", token,
                    MAX_LABEL_CHARS - 1);
            errors_exist = True;
        }
        else if (!symbol_flag) {
            memcpy(label, token, len - 2);
            label[len-2] = '\0';
            return True;
        }
        else {
            fprintf(stderr,
                    "Error: Unexpected appearance of an extra label \"%s\", only one label can appear per line\n",
                    token);
            errors_exist = True;
        }
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
            fprintf(stderr, "Error: Unknown data command \"%s\"\n", token);
    }
    /*free(data_name);*/
    return False;
}
boolean is_command(char * command_name){
    if (
        strcmp(command_name, "mov") == 0 ||
        strcmp(command_name, "cmp") == 0 ||
        strcmp(command_name, "add") == 0 ||
        strcmp(command_name, "sub") == 0 ||
        strcmp(command_name, "lea") == 0 ||
        strcmp(command_name, "clr") == 0 ||
        strcmp(command_name, "not") == 0 ||
        strcmp(command_name, "inc") == 0 ||
        strcmp(command_name, "dec") == 0 ||
        strcmp(command_name, "jmp") == 0 ||
        strcmp(command_name, "bne") == 0 ||
        strcmp(command_name, "jsr") == 0 ||
        strcmp(command_name, "red") == 0 ||
        strcmp(command_name, "prn") == 0 ||
        strcmp(command_name, "rts") == 0 ||
        strcmp(command_name, "stop") == 0
    ) {
        command = malloc(sizeof(command_name));
        strcpy(command, command_name);
        return True;
    }
    fprintf(stderr, "Error: Unknown command \"%s\"\n", command_name);
    return False;
}
boolean is_register (char * regis){
    if (
        strcmp(regis, "r0") == 0 ||
        strcmp(regis, "r1") == 0 ||
        strcmp(regis, "r2") == 0 ||
        strcmp(regis, "r3") == 0 ||
        strcmp(regis, "r4") == 0 ||
        strcmp(regis, "r5") == 0 ||
        strcmp(regis, "r6") == 0 ||
        strcmp(regis, "r7") == 0
    )
        return True;
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
void process_data_line(const char * token, char * line, boolean is_symbol){
    size_t len;
    int i = 0;
    char * stringContent;
    char * saveContent;
    if (is_symbol) {
        printf("Is a symbol\n");
        /*add_to_label_chart(label, DC, type, False, False);*/
    }
    if (strcmp(type, "string") == 0){
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
            fprintf(stderr, "Error: No opening and closing brackets in > %s  \n", token);
        }
    } else { /* .data */
        token = strtok(NULL, ",\n");
        while (token != NULL){
            saveContent = malloc(strlen(token));
            strcpy(saveContent, token);
            saveContent[strlen(saveContent)] = '\0';
            if (is_valid_param(saveContent)) {
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
        fprintf(stderr, "Error: Label needs to appear after \".extern\"\n");
        return;
    }
    token = strtok(NULL, delimiters);
    if (is_label(token)){
        printf("Good Label!!! %s\n", token);
        /*add_to_label_chart(label, 0, type, False, True);*/
    } else {
        fprintf(stderr, "Error: \"%s\" is not a valid label\n", token);
    }
}
void process_command_line(char token[], char * line, boolean is_symbol){
    if (is_symbol) {
        printf("Is a symbol\n");
        /*add_to_label_chart(label, IC, type(code), False, False);*/
    }
    if (
        strcmp(command, "mov") == 0 ||
        strcmp(command, "cmp") == 0 ||
        strcmp(command, "add") == 0 ||
        strcmp(command, "sub") == 0 ||
        strcmp(command, "lea") == 0
    ) {
        printf("Two operands\n");
        is_valid_two_operands(token);
    }
    else if (
        strcmp(command, "rts") == 0 ||
        strcmp(command, "stop") == 0
    ) {
        printf("No operands\n");
    }
    else {
        is_valid_operand(token);
        printf("One operand\n");
    }
}

boolean is_valid_param(char * number){
    int i=0;
    boolean isValidParam = True;
    while (number[0] == ' ' || number[0] == '\t')
        *number++;
    for(i ; i < strlen(number) ; i++) {
        if (i==0 && number[i] == '-')
            isValidParam = True;
        else if (number[i] != ' ' && number[i] != '\t' && !isdigit(number[i])) {
            fprintf(stderr, "Error: \"%s\" is not a valid number\n", number);
            return False;
        }
    }
    number = strpbrk(number, " ");
    if (number == NULL)
        return isValidParam;
    while (number[0] == ' ' || number[0] == '\t')
        *number++;
    if (strcmp(number, "") != 0) {
        fprintf(stderr, "Error: Missing comma before \"%s\"\n", number);
        isValidParam = False;
    }
    return isValidParam;
}

boolean is_valid_two_operands(char * operand){
    int i=0;
    int tokenCounter = 0;
    char * pt;
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
                fprintf(stderr, "Error: Not comma separated value\n");
                return False;
            }
        }
        printf("%s\n", operand);
        operandType = get_operand_type(operand);
        printf("OPERAND TYPE : %d\n", operandType);
        operand = strtok(NULL, ",\n");
        /* Decode the type  */
        if (tokenCounter > 2) {
            fprintf(stderr, "Error: Too many arguments\n");
            return False;
        }
    }
    if (tokenCounter == 1) {
        fprintf(stderr, "Error: Too few arguments\n");
        return False;
    }
    return True;
}

boolean is_valid_operand(char * operand){

}

int get_operand_type(char * operand) {
    if (operand[0] == '#'){
        *operand++;
        if (is_valid_param(operand))
            return IMMEDIATE;
        return ERROR;
    } else if (is_register(operand)) {
        return REGISTER;
    } else if (operand[0] == '&') {
        return INDIRECT;
    } else
        return DIRECT;
}