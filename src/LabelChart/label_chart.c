#include "label_chart.h"

void add_to_label_chart(Label ** label, char name[], int address, line_type type, boolean is_entry, boolean is_extern) {
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