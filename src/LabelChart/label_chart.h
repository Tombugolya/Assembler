#ifndef LABEL_CHART_H
#define LABEL_CHART_H
#include "../Common/common.h"

typedef struct label {
    char labelName[MAX_LABEL_CHARS];
    int address;
    line_type type;
    boolean external;
    boolean entry;
    struct label* next;
} Label;

void addToLabelChart(Label**, char*, int, line_type, boolean, boolean);
void printLabelChart(Label**);
void updateLabelValue(Label**, char*, int);
void updateLabelChart(Label**, int);
boolean isUniqueLabel(Label**, char*);
#endif /* LABEL_CHART_H */