#include "functions.h"

FILE * getFile(char *name){
    char *filename = concat(name, AS_EXTENSION);
    FILE *opened_file = fopen(filename, "r");
    if (opened_file  == NULL) {
        errorReport(FILE_NOT_FOUND, 0, filename);
        return opened_file;
    }
    free(filename);
    return opened_file;
}

char * concat(const char *s1, const char *s2) {
    char *result = malloc(strlen(s1) + strlen(s2) + 1); /* +1 for the null-terminator*/
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}

char * trimWhiteSpace(char *str) {
    char *end;
    while (isspace((unsigned char)*str))
        str++;
    if (*str == 0)
        return str;
    end = str + strlen(str) - 1;
    while(end > str && isspace((unsigned char)*end))
        end--;
    end[1] = '\0';
    return str;
}

void createTestFile(char *name) {
    FILE * filePointer;
    char *fileName = concat(name, TEST_EXTENSION); /* Concatenating the filename with the test extension*/
    filePointer = fopen(fileName, "w");
    fprintf(filePointer,"%*d\t%*d\n", 8, 10, 6, 10); /* Adding placeholder text for the IC DC later on to overwrite */
    fclose(filePointer);
    free(fileName);
}

void removeFiles(char *name) {
    char *obFile = concat(name, OB_EXTENSION);
    char *entFile = concat(name, ENT_EXTENSION);
    char *extFile = concat(name, EXT_EXTENSION);
    char *testFile = concat(name, TEST_EXTENSION);
    remove(obFile);
    remove(entFile);
    remove(extFile);
    remove(testFile);
    free(obFile);
    free(entFile);
    free(extFile);
    free(testFile);
}

void appendToBinaryString(unsigned int num, unsigned int bits, char *str) {
    unsigned int mask = (unsigned) 1 << (bits - 1);
    while (mask) {
        if (num & mask)
            strcat(str, "1");
        else
            strcat(str, "0");
        mask = mask >> (unsigned) 1;
    }
}
