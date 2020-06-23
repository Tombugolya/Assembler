#include "functions.h"

char * get_filename(char * file){
    size_t len = strlen(file);
    char * last_three;
    char * filename;
    int i;
    filename = (char *) malloc(len - FILE_TYPE_LEN);

    if (len > 3) {
        last_three = &file[len - FILE_TYPE_LEN];
        for(i=0 ; last_three[i] ; i++)
            last_three[i] = tolower(last_three[i]);
        if (strcmp(last_three, FILE_TYPE) == 0) {
            memcpy(filename, file, len - FILE_TYPE_LEN);
            filename[len - FILE_TYPE_LEN] = '\0';
            return filename;
        }
    }
    fprintf(stderr, "Error: \"%s\" is not an .as file\n", file);
    return NULL;
}

FILE * get_file(char * file){
    FILE * opened_file = fopen(file, "r");
    if (opened_file  == NULL) {
        fprintf(stderr, "Error: Cannot locate file \"%s\"\n", file);
        return opened_file;
    }
    return opened_file;
}
