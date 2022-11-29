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
    FILE *file;
    char fileToOpen[100];

    if (argc > 1) {
        strcpy(fileToOpen,argv[1]);
        strcpy(fileName,  getFileName(fileToOpen));
    }



    int failed = 0;
    do{
        if (argc == 1 && failed==1)
        {
            printf("Inserisci il nome del file da convertire (senza estensione):");
            scanf("%s", fileName);

            strcpy(fileToOpen, fileName);

            strcat(fileToOpen, ".asm");
        }
        file = fopen(fileToOpen, "r");
        if(file == NULL){
            printf("Il file non esiste, riprova.\n");
            failed = 1;
        }
    } while (file == NULL);
    fclose(file);


    pSymbolTable symbleTable = initSymbolTable();

    pLine code = readFile(fileToOpen, symbleTable);


    pBitString machineLanguageCode = convertToBitString(code,symbleTable);

    strcat(fileName, ".hack");
    writeFile(machineLanguageCode, fileName);
    printf("File convertito con successo!\n");
    getchar();

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
    return res;
}













