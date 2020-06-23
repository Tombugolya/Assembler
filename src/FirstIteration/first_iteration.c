#include "first_iteration.h"

int first_iteration(char * filename, FILE * file){
    int IC = 100;
    int DC = 0;
    char line[82];
    while(fgets(line, sizeof(line), file)){
        printf("%s", line); /*Print every line*/
    }
    return 1;
}
