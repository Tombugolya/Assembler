#ifndef LABEL_CHART_H
#define LABEL_CHART_H
#include "../Common/common.h"

typedef struct label {
    char * labelName;
    int address;
    line_type type;
    boolean external;
    boolean entry;
    struct label* next;
} Label;

void add_to_label_chart(Label**, char[], int, line_type, boolean, boolean);


#endif /* LABEL_CHART_H */