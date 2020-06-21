#include "main.h"

char * get_filename(char * file){
    size_t len = strlen(file);
    char * last_three;
    char * filename;

    filename = (char *) malloc(len - FILE_TYPE_LEN);

    if (len > 3) {
        last_three = &file[len - FILE_TYPE_LEN];
        if (strcmp(last_three, FILE_TYPE) == 0) {
            memcpy(filename, file, len - FILE_TYPE_LEN);
            filename[len - FILE_TYPE_LEN] = '\0';
            return filename;
        }
    }
    fprintf(stderr, "Error: \"%s\" is not an .as file\n", file);
    return NULL;
}