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

void printLabelChart(Label **label);

void updateLabelValue(Label **label, char *labelName, int value);

void updateLabelChart(Label **label, int IC);

boolean isUniqueLabel(Label **label, char *labelName, boolean report);

#endif /* LABEL_CHART_H */
