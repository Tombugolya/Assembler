#ifndef LABEL_CHART_H
#define LABEL_CHART_H
#include "../Common/common.h"
#include "../ErrorReport/error_report.h"

typedef struct Label {
    char labelName[MAX_LABEL_CHARS];
    int address;
    line_type type;
    boolean external;
    boolean entry;
    struct Label* next;
} Label;

void addToLabelChart(Label **label, char *name, int address, line_type type, boolean is_entry, boolean is_extern);

int getLabelAddress(Label **label, char *labelName);

void printLabelChart(Label **label);

void updateLabelAddress(Label **label, char *labelName, int value);

void updateLabelIsEntry(Label **label, char *labelName, boolean isEntry);

void updateLabelChart(Label **label, int IC);

boolean isUniqueLabel(Label **label, char *labelName, boolean report);

boolean labelIsExternal(Label **label, char *labelName);

void freeLabelChart(Label **label);

#endif /* LABEL_CHART_H */
