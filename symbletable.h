/**
 * @author:  Enirco Mazzotti (matricola: 0001071247)
 * @date:    16/11/2022
 * @note:    file header che implementa le funzioni per manipolare la symbol table
 * @project: Assemblatore per il linguaggio Assembly Hack
 * @file:    symbletable.h
 */

#ifndef ASSEMBLATORE_SYMBLETABLE_H
#define ASSEMBLATORE_SYMBLETABLE_H

#endif //ASSEMBLATORE_SYMBLETABLE_H

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

struct SymbleTable {
    int address;
    char symble[100];
    struct SymbleTable* next;
};
typedef struct SymbleTable* pSymbleTable;

pSymbleTable initSymbleTable();
pSymbleTable insertSymbleInQueue(pSymbleTable head, char *symble, int address);
pSymbleTable insertSymbleInHead(pSymbleTable head, char *symble, int address);
void printSymbleTable(pSymbleTable head);
int searchSymble(pSymbleTable , char*);
