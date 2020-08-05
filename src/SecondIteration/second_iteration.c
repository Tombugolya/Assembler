#include "second_iteration.h"

boolean errorsExist = False;

void second_iteration(char *filename, FILE *file, Label *labelHead) {
    char line[MAX_LINE_CHARS];
    char *token = NULL;
    rewind(file);
    while(fgets(line, sizeof(line), file)) {
        token = strtok(line, delimiters);
        while(token != NULL) {
            if (isEntry(token)) {
                processEntryLine(line, labelHead);
                token = NULL;
            }
            token = strtok(NULL, delimiters);
        }
    }
    printLabelChart(&labelHead);
    fclose(file);
    writeTestFileToOb(filename, labelHead);
    if (errorsExist)
        removeFiles(filename);
}

boolean isEntry(char *entryName) {
    size_t len = strlen(entryName);
    char *name = NULL;
    name = (char *) malloc(len - 1);
    strncpy(name, entryName + 1, len - 1);
    name[len - 1] = '\0';
    if (entryName[0] == '.') {
        if (strcmp(name, "entry") == 0)
            return True;
    }
    return False;
}

void processEntryLine(char *arguments, Label *labelHead) {
    arguments = strtok(NULL, delimiters);
    if (!isUniqueLabel(&labelHead, arguments, False))
        updateLabelIsEntry(&labelHead, arguments, True);
}

void writeTestFileToOb(char *filename, Label *labelHead) {
    FILE *testFile = NULL;
    FILE *obFile = NULL;
    char *filenameWithTestSuffix = NULL;
    char *filenameWithObSuffix = NULL;
    char *token = NULL;
    char *endPtr = NULL;
    char line[MAX_LINE_CHARS];
    char lineToCopy[MAX_LINE_CHARS];
    int address;
    int labelAddress;
    filenameWithTestSuffix = malloc(strlen(filename));
    strcpy(filenameWithTestSuffix, filename);
    strcat(filenameWithTestSuffix, ".test");
    filenameWithObSuffix = malloc(strlen(filename));
    strcpy(filenameWithObSuffix, filename);
    strcat(filenameWithObSuffix, ".ob");
    testFile = fopen(filenameWithTestSuffix, "r");
    obFile = fopen(filenameWithObSuffix, "w");
    printf("%s\n", filenameWithTestSuffix);
    while(fgets(line, sizeof(line), testFile)) {
        if (line[0] != RESERVED_SIGN) {
            strcpy(lineToCopy, line);
            fprintf(obFile, "%s", lineToCopy);
        } else {
            token = strtok(line, "\t");
            token++;
            address = strtol(token, &endPtr, 10);
            token = strtok(NULL, delimiters);
            if (token[0] == '&') {
                token++;
                if ((labelAddress = getLabelAddress(&labelHead, token)))
                    writeDistance(obFile, address, labelAddress);
                else
                    if (labelIsExternal(&labelHead, token))
                        errorsExist = errorReport(EXTERNAL_DISTANCE_INVALID, 0, token);
                    else
                        errorsExist = errorReport(NONEXISTENT_LABEL, 0, token);
            }
            else if ((labelAddress = getLabelAddress(&labelHead, token))) {
                    writeAddress(obFile, address, labelAddress);
            } else if (labelIsExternal(&labelHead, token)) {
                    writeExternal(obFile, address);
                    writeToExtFile(filename, token, address);
            } else {
                errorsExist = errorReport(NONEXISTENT_LABEL, 0, token);
            }
        }
    }
    writeToEntFile(filename, &labelHead);
    fclose(testFile);
    fclose(obFile);
    remove(filenameWithTestSuffix);
}
