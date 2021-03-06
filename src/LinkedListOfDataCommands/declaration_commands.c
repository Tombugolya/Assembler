#include "declaration_commands.h"

void addToDeclarationCommands(DeclarationCommands **list, int address, line_type type, int value) {
    DeclarationCommands *current;
    if(*list == NULL) { /* If it's a null head -- means that this list will be our new head */
        *list = (DeclarationCommands *)malloc(sizeof(DeclarationCommands));
        (*list) -> address = address;
        (*list) -> type = type;
        (*list) -> value = value;
        (*list) -> next = NULL;
    }
    else {
        current = *list;
        while(current -> next) /* Iterating until we reach next that equals to null -- which means it's a new spot in the list */
            current = current -> next;
        current -> next = (DeclarationCommands *)malloc(sizeof(DeclarationCommands));
        current -> next -> address = address;
        current -> next -> type = type;
        current -> next -> value = value;
        current -> next -> next = NULL;
    }
}

void updateDeclarationCommandsAddresses(DeclarationCommands **list, int IC) {
    DeclarationCommands *current = *list;
    while (current != NULL) {
        current -> address += IC;
        current = current -> next;
    }
}

void freeDeclarationCommands(DeclarationCommands *list) {
    DeclarationCommands  *current;
    while (list != NULL) {
        current = list;
        list = list -> next;
        free(current);
    }
}