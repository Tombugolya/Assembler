#include "first_iteration.h"
int IC = 100;
int DC = 0;
boolean errors_exist = False;
boolean symbol_flag;
void first_iteration(char * filename, FILE * file){
    int line_counter = 0;
    int token_counter;
    const char delimiters[] = " \t\n";
    char line[82];
    char * token;
    errors_exist = False;
    while(fgets(line, sizeof(line), file)){
        symbol_flag = False;
        token_counter = 0;
        line_counter++;
        token = strtok(line, delimiters);
        while(token != NULL) {
/*
            printf("String: %s\t\tLine no.%d\t\tToken No.%d\n", token, line_counter, ++token_counter);
*/
            if (is_a_symbol(token))
                symbol_flag = True;
            else if (is_data(token)) {
                if (is_extern(token))
                    process_extern_line(line, token);
                else
                    process_data_line(line, token, symbol_flag);
            }
            else if (is_command(token))
                process_command_line(line, token, symbol_flag);
            else if (is_comment(token))
                token = NULL;
            token = strtok(NULL, delimiters);
        }
    }
}

boolean is_a_symbol(char token[]){
    size_t len = strlen(token);
    if (isalpha(token[0]) && token[len - 1] == ':' ) {
        if (len >= MAX_SYMBOL_CHARS) {
            fprintf(stderr, "Error: Label name \"%s\" is too long, up to %d characters are allowed\n", token,
                    MAX_SYMBOL_CHARS - 1);
            errors_exist = True;
        }
        else if (!symbol_flag)
            return True;
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
boolean is_command(char token[]){
    return False;
}
boolean is_comment(char token[]){
    return False;
}
boolean is_valid_data_name(char * data_name){
    if (
        strcmp(data_name, "string") == 0 ||
        strcmp(data_name, "data") == 0 ||
        strcmp(data_name, "entry") == 0 ||
        strcmp(data_name, "extern") == 0
    )
        return True;
    return False;
}
boolean is_extern(char * data_name){
    if (strcmp(data_name, "extern") == 0)
        return True;
    return False;
}
void process_data_line(char token[], char* line, boolean is_symbol){

}
void process_extern_line(char token[], char* line){

}
void process_command_line(char token[], char* line, boolean is_symbol){

}
