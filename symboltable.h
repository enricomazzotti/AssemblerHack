/**
 * @author:  Enirco Mazzotti (matricola: 0001071247)
 * @date:    16/11/2022
 * @note:    file header che implementa le funzioni per manipolare la symbol table
 * @project: Assemblatore per il linguaggio Assembly Hack
 * @file:    symboltable.h
 */

#ifndef ASSEMBLATORE_SYMBLETABLE_H
#define ASSEMBLATORE_SYMBLETABLE_H

#endif //ASSEMBLATORE_SYMBLETABLE_H

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

struct SymbolTable {
    int address;
    char symbol[100];
    struct SymbolTable* next;
};
typedef struct SymbolTable* pSymbolTable;

pSymbolTable initSymbolTable();
pSymbolTable insertSymbolInQueue(pSymbolTable head, char *symbol, int address);
pSymbolTable insertSymbolInHead(pSymbolTable head, char *symbol, int address);
void printSymbolTable(pSymbolTable head);
int searchSymbol(pSymbolTable head, char* symbol);

