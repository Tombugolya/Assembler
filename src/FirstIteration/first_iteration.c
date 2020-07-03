#include "first_iteration.h"
#include "../LabelChart/label_chart.h"

int IC = 100;
int DC = 0;
boolean errors_exist = False;
boolean symbol_flag;
char label[MAX_SYMBOL_CHARS];
char * type;
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
        memset(label, 0, MAX_SYMBOL_CHARS);
        free(type);
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
                is_extern(token) ? process_extern_line(line, token) : process_data_line(line, token, symbol_flag);
            else if (is_command(token))
                process_command_line(line, token, symbol_flag);
            token = strtok(NULL, delimiters);
        }
    }
}

boolean is_label(char *token){
    size_t len = strlen(token);
    if (isalpha(token[0]) && token[len - 1] == ':' ) {
        if (len >= MAX_SYMBOL_CHARS) {
            fprintf(stderr, "Error: Label name \"%s\" is too long, up to %d characters are allowed\n", token,
                    MAX_SYMBOL_CHARS - 1);
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
            free(data_name);
            return True;
        }
        else
            fprintf(stderr, "Error: Unknown data command \"%s\"\n", token);
    }
    free(data_name);
    return False;
}
boolean is_command(char * token){
    if (
        strcmp(token, "mov") == 0 ||
        strcmp(token, "cmp") == 0 ||
        strcmp(token, "add") == 0 ||
        strcmp(token, "sub") == 0 ||
        strcmp(token, "lea") == 0 ||
        strcmp(token, "clr") == 0 ||
        strcmp(token, "not") == 0 ||
        strcmp(token, "inc") == 0 ||
        strcmp(token, "dec") == 0 ||
        strcmp(token, "jmp") == 0 ||
        strcmp(token, "bne") == 0 ||
        strcmp(token, "jsr") == 0 ||
        strcmp(token, "red") == 0 ||
        strcmp(token, "prn") == 0 ||
        strcmp(token, "rts") == 0 ||
        strcmp(token, "stop") == 0
    )
        return True;
    fprintf(stderr, "Error: Unknown command \"%s\"\n", token);
    return False;
}
boolean is_comment(const char token[]){
    if (token[0] == ';')
        return True;
    return False;
}
boolean is_extern(char * data_name){
    boolean bool = strcmp(data_name, "extern") == 0 ?  True : False;
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
    if (symbol_flag) {
        printf("Is a symbol\n");
        /*add_to_label_chart(label, DC, type, False, False);*/
    }
    if (strcmp(type, "string") == 0){
        token = strtok(NULL, delimiters);
        if (token[0]=='"' && token[len = (strlen(token) - 1)]=='"') {
            stringContent = malloc(len);
            strncpy(stringContent, token + 1, len-1);
            stringContent[strlen(stringContent)] = '\0';
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
                printf("%d: %d\n",DC ,atoi(saveContent));
                DC++;
            }
            token = strtok(NULL, ",\n");
        }
    }
    printf("SIZE OF DC: %d\n\n", DC);
}
void process_extern_line(char token[], char * line){

}
void process_command_line(char token[], char * line, boolean is_symbol){

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