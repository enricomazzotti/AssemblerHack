/**
 * @author:  Enirco Mazzotti (matricola: 0001071247)
 * @date:    16/11/2022
 * @note:    file sorgente che implementa le funzioni per manipolare la symbol table
 * @project: Assemblatore per il linguaggio Assembly Hack
 * @file:    symbletable.c
 */

#include "symbletable.h"

pSymbleTable initSymbleTable(){
    pSymbleTable head = NULL;
    head = insertSymbleInQueue(head, "R0", 0);
    insertSymbleInQueue(head, "R1", 1);
    insertSymbleInQueue(head, "R2", 2);
    insertSymbleInQueue(head, "R3", 3);
    insertSymbleInQueue(head, "R4", 4);
    insertSymbleInQueue(head, "R5", 5);
    insertSymbleInQueue(head, "R6", 6);
    insertSymbleInQueue(head, "R7", 7);
    insertSymbleInQueue(head, "R8", 8);
    insertSymbleInQueue(head, "R9", 9);
    insertSymbleInQueue(head, "R10", 10);
    insertSymbleInQueue(head, "R11", 11);
    insertSymbleInQueue(head, "R12", 12);
    insertSymbleInQueue(head, "R13", 13);
    insertSymbleInQueue(head, "R14", 14);
    insertSymbleInQueue(head, "R15", 15);
    insertSymbleInQueue(head, "SCREEN", 16384);
    insertSymbleInQueue(head, "KBD", 24576);
    insertSymbleInQueue(head, "SP", 0);
    insertSymbleInQueue(head, "LCL", 1);
    insertSymbleInQueue(head, "ARG", 2);
    insertSymbleInQueue(head, "THIS", 3);
    insertSymbleInQueue(head, "THAT", 4);
    return head;
}

pSymbleTable insertSymbleInQueue(pSymbleTable head, char symble[], int address){

    pSymbleTable newLine = (pSymbleTable) malloc(sizeof(struct SymbleTable));
    strcpy(newLine->symble, symble);
    newLine->address = address;
    newLine->next = NULL;
    if(head == NULL){
        return newLine;
    }
    pSymbleTable temp = head;

    while(temp->next != NULL ){
        temp = temp->next;
    }
    temp->next = newLine;

    return head;
}

pSymbleTable insertSymbleInHead(pSymbleTable head, char *symble, int address){
    pSymbleTable newLine = (pSymbleTable) malloc(sizeof(struct SymbleTable));
    strcpy(newLine->symble, symble);
    newLine->address = address;
    newLine->next = head;
    return newLine;
}

void printSymbleTable(pSymbleTable head){
    pSymbleTable temp = head;
    printf("Symble Table:\n");
    while(temp != NULL) {
        printf( "- %s - %d -\n", temp->symble, temp->address);
        temp = temp->next;
    }
    printf("End of Symble Table\n");
}

int searchSymble(pSymbleTable head, char* symble){
    pSymbleTable temp = head;
    while (temp != NULL){
        if (strcmp(temp->symble,symble) == 0){
            return temp->address;
        }
        temp = temp->next;
    }
    return -1;
}