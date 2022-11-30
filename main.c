/**
 * @author:  Enirco Mazzotti (matricola: 0001071247)
 * @date:    16/11/2022
 * @note:    Progetto 5 - Laboratorio Nand2Tetris
 * @project: Assemblatore per il linguaggio Assembly Hack
 */

#include <stdio.h>
#include <string.h>
#include <malloc.h>

#include "core.h"


char *getFileName(const char *str);

int main(int argc,char *argv[]) {
    char fileName[100];
    FILE *file = NULL;
    char fileToOpen[100];

    if (argc > 1) {
        strcpy(fileToOpen,argv[1]);
        strcpy(fileName,  getFileName(fileToOpen));

        file = fopen(fileToOpen, "r");
        if(file != NULL){
            fclose(file);

            pSymbolTable symbleTable = initSymbolTable();
            printf("Sto leggendo il file %s\n", fileToOpen);
            pLine code = readFile(fileToOpen, symbleTable);

            printf("Sto traducendo il file\n");
            pBitString machineLanguageCode = convertToBitString(code,symbleTable);

            strcat(fileName, ".hack");
            printf("Sto scrivendo il file %s\n", fileName);
            writeFile(machineLanguageCode, fileName);
            printf("Processo terminato\n");

        } else {
            printf("Il file non esiste.\n");
        }
    } else {
        printf("Nessun parametro passato.\n");
    }

    return 0;
}

char *getFileName(const char *str){
    const char delim = '.';
    size_t str_len = strlen(str), i = str_len;
    while (i > 0 && str[i] != delim)
        --i;
    if (!i)
        i = str_len;
    char *res = malloc(sizeof(char) * (i  + 1));
    strncpy(res, str, i);
    res[i] = '\0';
    return res;
}













