#include "data_commands.h"

void addToDataCommands(DataCommands** list, int address, line_type type, int value) {
    DataCommands *current;
    if(*list == NULL) {
        *list = (DataCommands *)malloc(sizeof(DataCommands));
        (*list) -> address = address;
        (*list) -> type = type;
        if (type == STRING) {
            (*list) -> character = value;
            (*list) -> num = 0;
        } else {
            (*list) -> num = value;
            (*list) -> character = '\0';
        }
        (*list) -> next = NULL;
    }
    else {
        current = *list;
        while(current -> next)
            current = current->next;
        current -> next = (DataCommands *)malloc(sizeof(DataCommands));
        current -> next -> address = address;
        current -> next -> type = type;
        if (type == STRING) {
            current -> next -> character = value;
            current -> next -> num = 0;
        } else {
            current -> next -> num = value;
            current -> next -> character = '\0';
        }
        current -> next -> next = NULL;
    }
}

void printDataCommands(DataCommands** list) {
    DataCommands * current = * list;
    printf("ADDRESS\t\tNUM\tCHAR\tTYPE\n");
    while (current != NULL) {
        printf("%d\t\t%d\t%c\t%d\t\n", current->address, current->num, current->character, current->type);
        current = current -> next;
    }
}