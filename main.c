#include "main.h"
#include "src/UtilFunctions/functions.h"
#include "src/FirstIteration/first_iteration.h"

int main(int argc, char *argv[]) {
    fileManagement(argc, argv);
    return 0;
}

void fileManagement(int argc, char *argv[]){
    if (argc > 1)
        processFiles(argc, argv);
    else
        errorReport(NO_FILES, 0);
}

void processFiles(int argc, char *argv[]){
    int i;
    char * filename;
    FILE * file;
    for (i = INPUT ; i < argc ; i++){
        filename = getFilename(argv[i]);
        file = getFile(argv[i]);
        if (filename && file)
            firstIteration(filename, file);
    }
}
