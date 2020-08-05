#include "second_iteration.h"

boolean errorsExist = False;

void secondIteration(char *filename, FILE *file, Label *labelHead) {
    rewind(file);
    readFileLineByLineSecondTime(file, labelHead);
    fclose(file);
    createObFile(filename, labelHead);
    freeLabelChart(&labelHead);
    if (errorsExist)
        removeFiles(filename);
}

void readFileLineByLineSecondTime(FILE *file, Label *labelHead) {
    char line[MAX_LINE_CHARS];
    char *token = NULL;
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
}


boolean isEntry(char *entryName) {
    if (entryName[0] == '.') {
        entryName++;
        if (strcmp(entryName, "entry") == 0)
            return True;
    }
    return False;
}

void processEntryLine(char *arguments, Label *labelHead) {
    arguments = strtok(NULL, delimiters);
    if (!isUniqueLabel(&labelHead, arguments, False))
        updateLabelIsEntry(&labelHead, arguments, True);
}

void createObFile(char *filename, Label *labelHead) {
    FILE *testFile = NULL;
    FILE *obFile = NULL;
    char *filenameWithTestSuffix = concat(filename, TEST_EXTENSION);
    char *filenameWithObSuffix = concat(filename, OB_EXTENSION);
    testFile = fopen(filenameWithTestSuffix, "r");
    obFile = fopen(filenameWithObSuffix, "w");
    transferContentFromTestToOb(testFile, obFile, filename, labelHead);
    writeToEntFile(filename, &labelHead);
    fclose(testFile);
    fclose(obFile);
    remove(filenameWithTestSuffix);
    free(filenameWithTestSuffix);
    free(filenameWithObSuffix);
}

void transferContentFromTestToOb(FILE *testFile, FILE *obFile, char *filename, Label *labelHead) {
    char *token = NULL;
    char *endPtr = NULL;
    char line[MAX_LINE_CHARS];
    char lineToCopy[MAX_LINE_CHARS];
    int address;
    int labelAddress;
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
}