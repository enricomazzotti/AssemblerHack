/**
 * @author:  Enirco Mazzotti (matricola: 0001071247)
 * @date:    16/11/2022
 * @note:    file sorgente che implementa le funzioni per manipolare la symbol table
 * @project: Assemblatore per il linguaggio Assembly Hack
 * @file:    symboltable.c
 */

#include "symboltable.h"

pSymbolTable initSymbolTable(){
    pSymbolTable head = NULL;
    head = insertSymbolInQueue(head, "R0", 0);
    insertSymbolInQueue(head, "R1", 1);
    insertSymbolInQueue(head, "R2", 2);
    insertSymbolInQueue(head, "R3", 3);
    insertSymbolInQueue(head, "R4", 4);
    insertSymbolInQueue(head, "R5", 5);
    insertSymbolInQueue(head, "R6", 6);
    insertSymbolInQueue(head, "R7", 7);
    insertSymbolInQueue(head, "R8", 8);
    insertSymbolInQueue(head, "R9", 9);
    insertSymbolInQueue(head, "R10", 10);
    insertSymbolInQueue(head, "R11", 11);
    insertSymbolInQueue(head, "R12", 12);
    insertSymbolInQueue(head, "R13", 13);
    insertSymbolInQueue(head, "R14", 14);
    insertSymbolInQueue(head, "R15", 15);
    insertSymbolInQueue(head, "SCREEN", 16384);
    insertSymbolInQueue(head, "KBD", 24576);
    insertSymbolInQueue(head, "SP", 0);
    insertSymbolInQueue(head, "LCL", 1);
    insertSymbolInQueue(head, "ARG", 2);
    insertSymbolInQueue(head, "THIS", 3);
    insertSymbolInQueue(head, "THAT", 4);
    return head;
}

pSymbolTable insertSymbolInQueue(pSymbolTable head, char symbol[], int address){

    pSymbolTable newLine = (pSymbolTable) malloc(sizeof(struct SymbolTable));
    strcpy(newLine->symbol, symbol);
    newLine->address = address;
    newLine->next = NULL;
    if(head == NULL){
        return newLine;
    }
    pSymbolTable temp = head;

    while(temp->next != NULL ){
        temp = temp->next;
    }
    temp->next = newLine;

    return head;
}

pSymbolTable insertSymbolInHead(pSymbolTable head, char *symbol, int address){
    pSymbolTable newLine = (pSymbolTable) malloc(sizeof(struct SymbolTable));
    strcpy(newLine->symbol, symbol);
    newLine->address = address;
    newLine->next = head;
    return newLine;
}

void printSymbolTable(pSymbolTable head){
    pSymbolTable temp = head;
    printf("Symble Table:\n");
    while(temp != NULL) {
        printf("- %s - %d -\n", temp->symbol, temp->address);
        temp = temp->next;
    }
    printf("End of Symble Table\n");
}

int searchSymbol(pSymbolTable head, char* symbol){
    pSymbolTable temp = head;
    while (temp != NULL){
        if (strcmp(temp->symbol, symbol) == 0){
            return temp->address;
        }
        temp = temp->next;
    }
    return -1;
}