#include "main.h"

int main(int argc, char *argv[]) {
    file_management(argc, argv);
    return 0;
}

void file_management(int argc, char *argv[]){
    if (argc > 1)
        process_files(argc, argv);
    else
        fprintf(stderr, "Error: No files attached\n");
}

void process_files(int argc, char *argv[]){
    int i = INPUT;
    char * filename;
    for (i ; i < argc ; i++){
        filename = get_filename(argv[i]);
        printf("%s\n", filename);
        if (filename)
            printf("");/* -> First iteration */
    }
}