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
            else if (is_data(token))
                process_data_line(line, token, symbol_flag);
            else if (is_entry(token))
                token = strtok(NULL, delimiters);
            else if (is_extern(token))
                process_extern_line(line, token);
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
        if (len >= MAX_SYMBOL_CHARS)
            fprintf(stderr, "Error: Label name \"%s\" is too long, up to %d characters are allowed\n", token, MAX_SYMBOL_CHARS-1);
        else if (!symbol_flag)
            return True;
        else
            fprintf(stderr, "Error: Unexpected appearance of an extra label \"%s\", only one label can appear per line\n", token);
    }
    return False;
}
boolean is_data(char token[]){
    return False;
}
boolean is_entry(char token[]){
    return False;
}
boolean is_extern(char token[]){
    return False;
}
boolean is_command(char token[]){
    return False;
}
boolean is_comment(char token[]){
    return False;
}
void process_data_line(char token[], char* line, boolean is_symbol){

}
void process_extern_line(char token[], char* line){

}
void process_command_line(char token[], char* line, boolean is_symbol){

}
