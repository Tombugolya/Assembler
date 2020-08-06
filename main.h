#ifndef MAIN_H
#define MAIN_H
#include <stdio.h>
#include "src/FirstIteration/first_iteration.h"
#include "src/UtilFunctions/functions.h"
#include "src/ErrorReport/error_report.h"

enum {INPUT = 1}; /* In argv the 1st argument (index 0) is always the name of the file, so hence INPUT for index 1 */

/* Function that checks if the user inputted at least one file in the command line */
void fileManagement(int argc, char **argv);

/* Function that processes the user inputted command line files */
void processFiles(int argc, char **argv);

#endif /* MAIN_H */
