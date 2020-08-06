#include "main.h"
#include "src/FirstIteration/first_iteration.h"

int main(int argc, char **argv) {
    fileManagement(argc, argv);
    return 0;
}

void fileManagement(int argc, char **argv) {
    if (argc > 1) /* At least 2 arguments needed since first argument is always the name of the program */
        processFiles(argc, argv);
    else
        errorReport(NO_FILES, 0);
}

void processFiles(int argc, char **argv) {
    int i;
    char *filename;
    FILE *file;
    for (i = INPUT ; i < argc ; i++) { /* Iterate over all of the files attached */
        filename = argv[i];
        file = getFile(filename);
        if (filename && file) {
            removeFiles(filename);
            firstIteration(filename, file);
        }
    }
}
