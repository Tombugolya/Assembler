#include "label_chart.h"

void addToLabelChart(Label ** label, char * name, int address, line_type type, boolean is_entry, boolean is_extern) {
    Label * current;
    if(* label == NULL) {
        * label = (Label *)malloc(sizeof(Label));
        strcpy((* label) -> labelName, name);
        (* label) -> address = address;
        (* label) -> type = type;
        (* label) -> entry = is_entry;
        (* label) -> external = is_extern;
        (* label) -> next = NULL;
    }
    else {
        current = * label;
        while(current -> next)
            current = current->next;
        current -> next = (Label *)malloc(sizeof(Label));
        strcpy(current -> next -> labelName, name);
        current -> next -> address = address;
        current -> next -> type = type;
        current -> next -> entry = is_entry;
        current -> next -> external = is_extern;
        current -> next -> next = NULL;
    }
}

void updateLabelValue(Label** label, char * labelName, int value) {
    Label * current = * label;
    while (current != NULL) {
        if (strcmp(current -> labelName, labelName) == 0) {
            current -> address = value;
            return;
        }
        current = current -> next;
    }
}

void updateLabelChart(Label** label, int IC) {
    Label * current = * label;
    while (current != NULL) {
        if (current -> type != CODE && !current -> external) {
            current -> address += IC;
        }
        current = current -> next;
    }
}

void printLabelChart(Label ** label) {
    Label * current = * label;
    printf("NAME\t\tADDRESS\tTYPE\tENTRY\tEXTERN\n");
    while (current != NULL) {
        printf("%s\t\t%d\t%d\t%d\t%d\t\n", current->labelName, current->address, current->type, current->entry, current->external);
        current = current -> next;
    }
}

boolean isUniqueLabel(Label** label, char * labelName) {
    Label * current = * label;
    while (current != NULL) {
        if (strcmp(current -> labelName, labelName) == 0)
            return False;
        current = current -> next;
    }
    return True;
}
