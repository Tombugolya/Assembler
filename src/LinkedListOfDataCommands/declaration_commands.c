#include "declaration_commands.h"

void addToDeclarationCommands(DeclarationCommands **list, int address, line_type type, int value) {
    DeclarationCommands *current;
    if(*list == NULL) {
        *list = (DeclarationCommands *)malloc(sizeof(DeclarationCommands));
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
        current -> next = (DeclarationCommands *)malloc(sizeof(DeclarationCommands));
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

void updateDeclarationCommands(DeclarationCommands **list, int IC) {
    DeclarationCommands * current = * list;
    while (current != NULL) {
        current -> address += IC;
        current = current -> next;
    }
}

void freeDeclarationCommands(DeclarationCommands **list) {
    free(*list);
}