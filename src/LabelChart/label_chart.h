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

void addToLabelChart(LabelChart **label, char *name, int address, line_type type, boolean is_entry, boolean is_extern);

int getLabelAddress(LabelChart **label, char *labelName);

void updateLabelAddress(LabelChart **label, char *labelName, int value);

void updateLabelIsEntry(LabelChart **label, char *labelName, boolean isEntry);

void updateLabelChart(LabelChart **label, int IC);

boolean isUniqueLabel(LabelChart **label, char *labelName, boolean report);

boolean labelIsExternal(LabelChart **label, char *labelName);

void freeLabelChart(LabelChart *label);

#endif /* LABEL_CHART_H */
