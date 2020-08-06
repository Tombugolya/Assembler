#ifndef ASSEMBLER_SECOND_ITERATION_H
#define ASSEMBLER_SECOND_ITERATION_H

#include "../Common/common.h"
#include "../LabelChart/label_chart.h"
#include "../Decode/decode.h"

/* Second iteration of the user inputted file.
 * Checks each line to find .entry declarations.
 * For each entry the relevant label in the Label Chart will be updated with the entry flag set to true.
 * The .test file from the first iteration will be copied over to the final .ob file.
 * Reserved lines will be filled out during this iteration, with them also the .ent and .ext files.
 * param filename - the name of the file
 * param file - the file to read
 * param labelHead - the Label Chart from the first iteration
*/
void secondIteration(char *filename, FILE *file, LabelChart *labelHead);

/* Reads the file line by line and sends it over to the relevant function
 * param file - the file to read
 * param labelHead - the label chart
*/
void readFileLineByLineSecondTime(FILE *file, LabelChart *labelHead);

/* Checks if the line is an .entry declaration line and returns the relevant boolean value
 * param entryName - the line to check
*/
boolean isEntry(char *entryName);

/* Parses the entry line and updates the label chart if the label exists
 * param arguments - the arguments to check
 * param labelHead - the label chart
*/
void processEntryLine(char *arguments, LabelChart *labelHead);

/* Creates the final .ob, .ent and .ext files
 * param filename - the name of the file
 * param labelHead - the label chart
*/
void createOutputFiles(char *filename, LabelChart *labelHead);

/* Copies the content from the .test file to the .ob file and checks for reserved lines
 * param testFile - the test file to copy from
 * param obFile - the ob file to paste to
 * param filename - the name of the file
 * param labelHead - the label chart
*/
void transferContentFromTestToOb(FILE *testFile, FILE *obFile, char *filename, LabelChart *labelHead);

/* Handles the reserved lines from the first iteration and overwrites them to the proper address / distance of the label
 * param line - the current line on the test file
 * param obFile - the ob file
 * param filename - the name of the file
 * param labelHead - the label chart
*/
void overwriteReservedLines(char *line, FILE *obFile, char *filename, LabelChart *labelHead);

#endif
