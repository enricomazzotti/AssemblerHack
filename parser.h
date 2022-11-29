/**
 * @author:  Enirco Mazzotti (matricola: 0001071247)
 * @date:    16/11/2022
 * @note:    file header che implementa le funzioni per manipolare le stringhe
 * @project: Assemblatore per il linguaggio Assembly Hack
 * @file:    parser.h
 */

#ifndef ASSEMBLATORE_PARSER_H
#define ASSEMBLATORE_PARSER_H

#endif //ASSEMBLATORE_PARSER_H

#include <string.h>

void trimAll(char *str); // Rimuove gli spazi bianchi e le tabulazioni da una stringa
void removeComments(char *str); // Rimuove i commenti da una stringa
int parseint(const char *str); // Converte una stringa in un intero
void base10ToBase2on16bit(int num, char *bitString); // Converte un intero in una stringa binaria
int identifyInstruction(const char *inst); // Ritorna 0 se label, 1 se a inst, 2 c inst
void removeBrackets(char*); // Rimuove le patentesi da una stringa, tipicamente una label
void convertIntToString(char *str, int num); // Converte un intero in una stringa
void reverseString(char *str); // Inverte l'ordine dei caratteri nella stringa
void getDest(char *, char *);  // Ottiene la sustring dest da una C instruction
void getComp(char *, char *);  // Ottiene la sustring comp da una C instruction
void getJump(char *, char *);  // Ottiene la sustring jump da una C instruction