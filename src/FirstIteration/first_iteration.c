#include "first_iteration.h"
int IC = 100;
int DC = 0;
boolean errors_exist = False;
void first_iteration(char * filename, FILE * file){
    int line_counter = 0;
    int token_counter;
    const char delimiters[] = " \t";
    char line[82];
    char * token;
    boolean symbol_flag;

    while(fgets(line, sizeof(line), file)){
        symbol_flag = False;
        token_counter = 0;
        line_counter++;
        token = strtok(line, delimiters);
        while(token != NULL) {
            printf("String: %s\t\tLine no.%d\t\tToken No.%d\n", token, line_counter, ++token_counter);
            /*if (is_a_symbol(token))
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
                token = NULL;*/
            token = strtok(NULL, delimiters);
        }
    }
}
