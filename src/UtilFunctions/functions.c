#include "functions.h"

char * getFilename(char *file){
    size_t len = strlen(file);
    char * last_three;
    char * filename;
    int i;
    filename = (char *) malloc(len - FILE_TYPE_LEN);

    if (len > 3) {
        last_three = &file[len - FILE_TYPE_LEN];
        for(i=0 ; last_three[i] ; i++)
            last_three[i] = (char) tolower(last_three[i]);
        if (strcmp(last_three, FILE_TYPE) == 0) {
            memcpy(filename, file, len - FILE_TYPE_LEN);
            filename[len - FILE_TYPE_LEN] = '\0';
            return filename;
        }
    }
    errorReport(INVALID_AS_FILE, 0, file);
    return NULL;
}

FILE * getFile(char *file){
    FILE * opened_file = fopen(file, "r");
    if (opened_file  == NULL) {
        errorReport(FILE_NOT_FOUND, 0, file);
        return opened_file;
    }
    return opened_file;
}

char * trimWhiteSpace(char *str) {
    char *end;
    while(isspace((unsigned char)*str)) str++;
    if(*str == 0)
        return str;
    end = str + strlen(str) - 1;
    while(end > str && isspace((unsigned char)*end)) end--;
    end[1] = '\0';
    return str;
}

void createObFile(char *name) {
    FILE * filePointer;
    char *fileName;
    fileName = malloc(strlen(name));
    strcpy(fileName, name);
    strcat(fileName, ".ob");
    filePointer = fopen(fileName, "w");
    fprintf(filePointer,"%*d\t%*d\n", 8, 10, 6, 10);
    fclose(filePointer);
}

void removeFiles(char *name) {
    char *obFile;
    char *entFile;
    char *extFile;
    obFile = malloc(strlen(name));
    entFile = malloc(strlen(name));
    extFile = malloc(strlen(name));
    strcpy(obFile, name);
    strcpy(entFile, name);
    strcpy(extFile, name);
    strcat(obFile, ".ob");
    strcat(entFile, ".ent");
    strcat(extFile, ".ext");
    remove(obFile);
    remove(entFile);
    remove(extFile);
}

void appendToBinaryString(unsigned int x, unsigned int bits, char *string) {
    unsigned int mask = (unsigned) 1 << (bits - 1);
    while (mask) {
        if (x & mask)
            strcat(string, "1");
        else
            strcat(string, "0");
        mask = mask >> (unsigned) 1;
    }
}
