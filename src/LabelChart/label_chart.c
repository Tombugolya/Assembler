#include "label_chart.h"

void addToLabelChart(LabelChart **label, char *name, int address, line_type type, boolean is_entry, boolean is_extern) {
    LabelChart *current;
    if(*label == NULL) {
        *label = (LabelChart *)malloc(sizeof(LabelChart));
        strcpy((* label) -> labelName, name);
        (*label) -> address = address;
        (*label) -> type = type;
        (*label) -> entry = is_entry;
        (*label) -> external = is_extern;
        (*label) -> next = NULL;
    }
    else {
        current = *label;
        while(current -> next)
            current = current->next;
        current -> next = (LabelChart *) malloc(sizeof(LabelChart));
        strcpy(current -> next -> labelName, name);
        current -> next -> address = address;
        current -> next -> type = type;
        current -> next -> entry = is_entry;
        current -> next -> external = is_extern;
        current -> next -> next = NULL;
    }
}

int getLabelAddress(LabelChart **label, char *labelName) {
    LabelChart *current = *label;
    while (current != NULL) {
        if (strcmp(current -> labelName, labelName) == 0)
            return current -> address;
        current = current -> next;
    }
    return 0;
}

void updateLabelAddress(LabelChart **label, char *labelName, int value) {
    LabelChart *current = *label;
    while (current != NULL) {
        if (strcmp(current -> labelName, labelName) == 0) {
            current -> address = value;
            return;
        }
        current = current -> next;
    }
}

void updateLabelIsEntry(LabelChart **label, char *labelName, boolean isEntry) {
    LabelChart *current = *label;
    while (current != NULL) {
        if (strcmp(current -> labelName, labelName) == 0) {
            current -> entry = isEntry;
            return;
        }
        current = current -> next;
    }
}

void updateLabelChart(LabelChart **label, int IC) {
    LabelChart *current = *label;
    while (current != NULL) {
        if (current -> type != INSTRUCTION && !current -> external) {
            current -> address += IC;
        }
        current = current -> next;
    }
}

boolean isUniqueLabel(LabelChart **label, char *labelName, boolean report) {
    LabelChart *current = *label;
    while (current != NULL) {
        if (strcmp(current -> labelName, labelName) == 0) {
            if (report) errorReport(NOT_UNIQUE_LABEL, 0, labelName);
            return False;
        }
        current = current -> next;
    }
    return True;
}

boolean labelIsExternal(LabelChart **label, char *labelName) {
    LabelChart *current = *label;
    while (current != NULL) {
        if (strcmp(current -> labelName, labelName) == 0) {
            return current -> external;
        }
        current = current -> next;
    }
    return False;
}

void freeLabelChart(LabelChart *label) {
    LabelChart  *current;
    while (label != NULL) {
        current = label;
        label = label -> next;
        free(current);
    }
}
