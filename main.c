/**
 * @author:  Enirco Mazzotti (matricola: 0001071247)
 * @date:    16/11/2022
 * @note:    Progetto 5 - Laboratorio Nand2Tetris
 * @project: Assemblatore per il linguaggio Assembly Hack
 */

#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdbool.h>
#include <ctype.h>

struct Line {
    int address;
    char codeLine[100];
    struct Line* next;
};

typedef struct Line* pLine;

struct BitString {
    char machineLangaugeLine[100];
    struct BitString* next;
};

typedef struct BitString* pBitString;

// Prototipi delle funzioni

pLine readFile(char *fileName); // Legge il file e ritorna una lista di linee di codice lette

pBitString convertToBitString(pLine); // Converte la lista di linee di codice in una lista di stringhe binarie (lingiaggio macchina)

void writeFile(pBitString head, char *fileName); // Scrive il file di output

pLine insertLineInQueue(pLine head, char *line); // Inserisce una nuova linea di codice in coda alla lista

pBitString insertBitStringInQueue(pBitString head, char *line); // Inserisce una nuova stringa binaria in coda alla lista

void trimAll(char *str); // Rimuove gli spazi bianchi e le tabulazioni da una stringa

void writeFileDebug(pLine head, char *fileName); // Scrive il file di debug

int main() {
    char fileName[100];
    FILE *file;
    do{
        printf("Inserisci il nome del file da convertire (senza estensione): ");
        scanf("%s", fileName);
        strcat(fileName, ".asm");
        file = fopen(fileName, "r");
        if(file == NULL){
            printf("Il file non esiste, riprova.\n");
        }
    } while (file == NULL);
    fclose(file);

    pLine code = readFile(fileName);
    writeFileDebug(code, "debug.asm");
    //pBitString bitString = convertToBitString(code);
    //writeFile(bitString, fileName);
    //system('pause');
    return 0;
}

pLine insertLineInQueue(pLine head, char *line){
    pLine newLine = (pLine) malloc(sizeof(struct Line));
    strcpy(newLine->codeLine, line);
    newLine->next = NULL;
    if(head == NULL){
        return newLine;
    }
    pLine temp = head;
    while(temp->next != NULL){
        temp = temp->next;
    }
    temp->next = newLine;
    return head;
}

pLine readFile(char *fileName){
    FILE *file = fopen(fileName, "r");
    pLine head = NULL;
    char line[100];
    while(fgets(line, 512, file) != NULL){
        trimAll(line);
        if (*line != '\n' && *(line+1) != '\0' ) { // le righe vuote vengono omesse
            head = insertLineInQueue(head, line);
        }

    }
    return head;
}

pBitString convertToBitString(pLine){
    // TODO: Implementare la funzione che converte la lista di linee di codice in una lista di stringhe binarie

    return NULL;
}

void writeFile(pBitString head, char *fileName){
    FILE *file = fopen(fileName, "w");
    pBitString temp = head;
    while(temp != NULL) {
        fprintf(file, "%s", temp->machineLangaugeLine);
        temp = temp->next;
    }
}

void trimAll(char *str){
    char *new = str;
    while(*new != '\0'){
        if(*new != ' ' && *new != '\t'){
            *str = *new;
            str++;
        }
        new++;
    }
    *str = '\0';
}
//(*str >= 'a'&&*str <= 'z')||(*str >= 'A'&&*str <= 'Z')||(*str >= '@')||(*str >= '(')||(*str >= ')')||(*str >= '\n')

void writeFileDebug(pLine head, char *fileName){
    FILE *file = fopen(fileName, "w");
    pLine temp = head;
    while(temp != NULL) {
        fprintf(file, "%s", temp->codeLine);
        temp = temp->next;
    }
}