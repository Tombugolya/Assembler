#include "second_iteration.h"

boolean errorsExist = False;

void secondIteration(char *filename, FILE *file, LabelChart *labelHead) {
    rewind(file); /* Rewind because we iterated throughout the file once in firstIteration*/
    readFileLineByLineSecondTime(file, labelHead);
    fclose(file); /* At this point we are done with the user inputted file */
    createOutputFiles(filename, labelHead);
    freeLabelChart(labelHead);
    if (errorsExist)
        removeFiles(filename);
}

void readFileLineByLineSecondTime(FILE *file, LabelChart *labelHead) {
    char line[MAX_LINE_CHARS];
    char *token = NULL;

    while(fgets(line, sizeof(line), file)) {
        token = strtok(line, DELIMITERS);
        while(token != NULL) {
            if (isEntry(token)) {
                processEntryLine(line, labelHead);
                token = NULL;
            }
            token = strtok(NULL, DELIMITERS);
        }
    }
}


boolean isEntry(char *entryName) {
    if (entryName[0] == DECLARATION_SIGN) {
        entryName++;
        if (strcmp(entryName, "entry") == 0)
            return True;
    }
    return False;
}

void processEntryLine(char *arguments, LabelChart *labelHead) {
    arguments = strtok(NULL, DELIMITERS);

    if (!isUniqueLabel(&labelHead, arguments, False)) /* Means that the label exists and we can update its entry flag */
        updateLabelIsEntry(&labelHead, arguments, True);
}

void createOutputFiles(char *filename, LabelChart *labelHead) {
    FILE *testFile = NULL;
    FILE *obFile = NULL;
    char *filenameWithTestSuffix = concat(filename, TEST_EXTENSION);
    char *filenameWithObSuffix = concat(filename, OB_EXTENSION);
    testFile = fopen(filenameWithTestSuffix, "r");  /* Reading the temporary .test file*/
    obFile = fopen(filenameWithObSuffix, "w");      /* Writing the output .ob file*/
    transferContentFromTestToOb(testFile, obFile, filename, labelHead);
    writeToEntFile(filename, &labelHead);
    fclose(testFile);
    fclose(obFile);
    remove(filenameWithTestSuffix);
    free(filenameWithTestSuffix);
    free(filenameWithObSuffix);
}

void transferContentFromTestToOb(FILE *testFile, FILE *obFile, char *filename, LabelChart *labelHead) {
    char line[MAX_LINE_CHARS];
    char lineToCopy[MAX_LINE_CHARS];

    while(fgets(line, sizeof(line), testFile)) {
        if (line[0] != RESERVED_SIGN) { /* If it doesn't contain the '?' sign for reserved lines -- means it is a finished line */
            strcpy(lineToCopy, line);
            fprintf(obFile, "%s", lineToCopy);
        } else { /* Reserved line that needs to be decoded and written */
            overwriteReservedLines(line, obFile, filename, labelHead);
        }
    }
}

void overwriteReservedLines(char *line, FILE *obFile, char *filename, LabelChart *labelHead) {
    char *token = NULL;
    char *endPtr = NULL;
    int address;
    int labelAddress;
    token = strtok(line, "\t");
    token++;
    address = strtol(token, &endPtr, 10);
    token = strtok(NULL, DELIMITERS);

    if (token[0] == DISTANCE_SIGN) { /* If it has the '&' sign it means that we need to calculate the distance (INDIRECT addressing mode) */
        token++;
        if ((labelAddress = getLabelAddress(&labelHead, token)))
            writeDistance(obFile, address, labelAddress);
        else { /* Means that getLabelAddress returned 0 -- which means that it is either an external label or simply a nonexistent one */
            if (labelIsExternal(&labelHead, token))
                errorsExist = errorReport(EXTERNAL_DISTANCE_INVALID, 0, token);
            else
                errorsExist = errorReport(NONEXISTENT_LABEL, 0, token);
        }
    }
    else if ((labelAddress = getLabelAddress(&labelHead, token))) { /* If it's a non external or non entry label */
        writeLabelAddress(obFile, address, labelAddress);
    } else if (labelIsExternal(&labelHead, token)) { /* If it's an external label*/
        writeExternal(obFile, address);
        writeToExtFile(filename, token, address);
    } else { /* Nonexistent label */
        errorsExist = errorReport(NONEXISTENT_LABEL, 0, token);
    }
}