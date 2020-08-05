#ifndef LABEL_CHART_H
#define LABEL_CHART_H
#include "../Common/common.h"
#include "../ErrorReport/error_report.h"

/* Label linked list for all of the labels the program comes across throughout the first iteration.
 * Labels in a beginning of a line start begin with an alpha and end with a colon eg. "LABEL:"
 * Label charts are referenced throughout the first and second iteration and are used for the .ext and .ent files
 * param labelName - the name of the label (it can be up to 30 chars)
 * param address - the address where the label was found
 * param type - the type of line it is
 * param external - boolean value for whether the label is external or not
 * param entry - boolean value for whether the label is an entry or not
 * param next - the next label in the linked list
*/
typedef struct LabelChart {
    char labelName[MAX_LABEL_CHARS];
    int address;
    line_type type;
    boolean external;
    boolean entry;
    struct LabelChart* next;
} LabelChart;

/* Adds a new label to the label chart
 * param label - the head of the label chart
 * param name - the name of the new label
 * param address - the address of the label
 * param type - the type of line related to the label
 * param is_entry - entry flag for the label
 * param is_extern - extern flag for the label
*/
void addToLabelChart(LabelChart **label, char *name, int address, line_type type, boolean is_entry, boolean is_extern);

/* Returns the label address for the relevant name given as a parameter
 * param label - the head of the label chart
 * param labelName - the name of the label to find within the label chart
*/
int getLabelAddress(LabelChart **label, char *labelName);

/* Updates the address for the relevant label with the same name as given in the arguments
 * param label - the head of the label chart
 * param labelName - the name of the label to update
 * param value - the new address to store
*/
void updateLabelAddress(LabelChart **label, char *labelName, int value);

/* Updates the is_entry value for the relevant label
 * param label - the head of the label chart
 * param labelName - the name of the label to update
 * param isEntry - the boolean value to store
*/
void updateLabelIsEntry(LabelChart **label, char *labelName, boolean isEntry);

/* Updates the addresses for instruction and non external typed labels with the IC value.
 * This is updated after the first iteration finishes with writing the instruction lines.
 * param label - the head of the label chart
 * param IC - the value to increment the addresses for the relevant labels
*/
void updateLabelChartAddresses(LabelChart **label, int IC);

/* Returns a boolean value depending if it is a unique label or not
 * param label - the head of the label chart
 * param labelName - the name of the label to check if it already exists in the label chart or not
 * param report - flag for reporting an error in case the label is not unique
*/
boolean isUniqueLabel(LabelChart **label, char *labelName, boolean report);

/* Returns a boolean value depending if the label is external or not
 * param label - the head of the label chart
 * param labelName - the name of the label to check the condition
*/
boolean labelIsExternal(LabelChart **label, char *labelName);

/* Frees the memory allocated for the label chart
 * param label - the head of the label chart
*/
void freeLabelChart(LabelChart *label);

#endif /* LABEL_CHART_H */
