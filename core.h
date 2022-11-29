/**
 * @author:  Enirco Mazzotti (matricola: 0001071247)
 * @date:    16/11/2022
 * @note:    file header che implementa il core dell'assemblatore
 * @project: Assemblatore per il linguaggio Assembly Hack
 * @file:    core.h
 */


#ifndef ASSEMBLATORE_CORE_H
#define ASSEMBLATORE_CORE_H

#endif //ASSEMBLATORE_CORE_H

#include "symboltable.h"
#include "parser.h"

struct Line {
    char codeLine[100];
    struct Line* next;
};
typedef struct Line* pLine;

struct BitString {
    int address;
    char machineLangaugeLine[17];
    struct BitString* next;
};
typedef struct BitString* pBitString;


//assemlatore.c
pLine readFile(char *fileName, pSymbolTable); // Legge il file e ritorna una lista di linee di codice lette
void writeFile(pBitString head, char *fileName); // Scrive il file di output
pBitString convertToBitString(pLine, pSymbolTable symbleTable); // Converte la lista di linee di codice in una lista di stringhe binarie (lingiaggio macchina)
void convertAinstruction(char *line, char *bitString); // Converte una istruzione A in una stringa binaria
int convertCinstruction(char *line, char *bitString); // Converte una istruzione C in una stringa binaria
int isEligibleA(char *str);
int getLastAddress(pBitString head); // Ritorna l'ultimo indirizzo utilizzato
pLine insertLineInQueue(pLine head, char *line); // Inserisce una nuova linea di codice in coda alla lista
pBitString insertBitStringInQueue(pBitString head, char *line); // Inserisce una nuova stringa binaria in coda alla lista

