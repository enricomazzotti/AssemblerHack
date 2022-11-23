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
    char codeLine[100];
    struct Line* next;
};

typedef struct Line* pLine;

struct BitString {
    int address;
    char machineLangaugeLine[100];
    struct BitString* next;
};

typedef struct BitString* pBitString;

struct SymbleTable {
    int address;
    char symble[100];
    struct SymbleTable* next;
};

typedef struct SymbleTable* pSymbleTable;
// Prototipi delle funzioni

pLine readFile(char *fileName, pSymbleTable); // Legge il file e ritorna una lista di linee di codice lette

pBitString convertToBitString(pLine); // Converte la lista di linee di codice in una lista di stringhe binarie (lingiaggio macchina)

void writeFile(pBitString head, char *fileName); // Scrive il file di output

pLine insertLineInQueue(pLine head, char *line); // Inserisce una nuova linea di codice in coda alla lista

pBitString insertBitStringInQueue(pBitString head, char *line); // Inserisce una nuova stringa binaria in coda alla lista

void trimAll(char *str); // Rimuove gli spazi bianchi e le tabulazioni da una stringa

void removeComments(char *str); // Rimuove i commenti da una stringa

void writeFileDebug(pLine head, char *fileName); // Scrive il file di debug

void convertAinstuction(char *line, char *bitString); // Converte una istruzione A in una stringa binaria

int parseint(char *str); // Converte una stringa in un intero

void base10ToBase2(int num, char *bitString); // Converte un intero in una stringa binaria

pSymbleTable initSymbleTable();

pSymbleTable insertSymbleInQueue(pSymbleTable head, char *symble, int address);

//int getSymbolAddress(char *symbol, pBitString head); // Ritorna l'indirizzo di un simbolo

int getLastAddress(pBitString head); // Ritorna l'ultimo indirizzo utilizzato

int identifyInstruction(const char *inst); // Ritorna 0 se label, 1 se a inst, 2 c inst

void removeBrackets(char*);

void printSymbleTable(pSymbleTable head);

int main() {
    char fileName[100];
    FILE *file;
    do{
        printf("Inserisci il nome del file da convertire (senza estensione): ");
        scanf("%s", fileName);
        char fileToOpen[100];
        strcpy(fileToOpen, fileName);
        strcat(fileName, ".asm");
        file = fopen(fileName, "r");
        if(file == NULL){
            printf("Il file non esiste, riprova.\n");
        }
    } while (file == NULL);
    fclose(file);

    pSymbleTable symbleTable = initSymbleTable();


    pLine code = readFile(fileName, symbleTable);

    //printSymbleTable(symbleTable);
    pBitString machineLanguageCode = convertToBitString(code);
    writeFileDebug(code, "debug.asm");
    strcat(fileName, ".hack");
    writeFile(machineLanguageCode, fileName);
    printf("File convertito con successo!\n");

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

pBitString insertBitStringInQueue(pBitString head, char *line){
    pBitString newLine = (pBitString) malloc(sizeof(struct BitString));
    strcpy(newLine->machineLangaugeLine, line);
    newLine->address = getLastAddress(head) + 1;
    newLine->next = NULL;
    if(head == NULL){
        return newLine;
    }
    pBitString temp = head;
    while(temp->next != NULL){
        temp = temp->next;
    }
    temp->next = newLine;
    return head;
}

pLine readFile(char *fileName,pSymbleTable symbleTable){
    int  contatore = 0;
    FILE *file = fopen(fileName, "r");
    pLine head = NULL;
    char line[100];
    while(fgets(line, 100, file) != NULL){
        trimAll(line);
        removeComments(line);

        if (*line != '\0' ) { // le righe vuote vengono rimosse tranne l'ultima riga che rimane vuota
            // identifica l'istruzione
            if(identifyInstruction(line)==0) {
                removeBrackets(line);
                insertSymbleInQueue(symbleTable,line,contatore);
            } else {

                head = insertLineInQueue(head, line);
                contatore++;
            }
        }

    }
    return head;
}

//remove () from str
void removeBrackets(char* str){
    char *temp = str;

    while (*temp != '\0'){
        if (*temp != '(' && *temp != ')'){
            *str = *temp;
            str++;
        }
        temp++;
    }
    *str = '\0';
}

pBitString convertToBitString(pLine headLine){
    // TODO: Implementare la funzione che converte la lista di linee di codice in una lista di stringhe binarie
    pBitString head = NULL;
    pLine temp = headLine;
    /*
     while (headLine != NULL){
        if(headLine->codeLine[0] == '@'){
            char bitString[16];
            //convertAinstuction(headLine->codeLine, bitString);
            head = insertBitStringInQueue(head, bitString);
        } else{
            char bitString[16];

            head = insertBitStringInQueue(head, bitString);
        }
        headLine = headLine->next;
    }
     */

    while (headLine != NULL){
        if(headLine->codeLine[0] == '@'){
            char bitString[16];
            //convertAinstuction(headLine->codeLine, bitString);
            head = insertBitStringInQueue(head, bitString);
        } else{
            char bitString[16];

            head = insertBitStringInQueue(head, bitString);
        }
        headLine = headLine->next;
    }


    return head;
}

void convertAinstuction(char *line, char *bitString){
    if (*line== '@'){
        line++;
        int num = parseint(line);
        base10ToBase2(num, bitString);
    }
}

int parseint(char *str){
    int i = 0;
    int num = 0;
    while(str[i] != '\0'){
        num = num * 10 + (str[i] - '0');
        i++;
    }
    return num;
}

void base10ToBase2(int num, char *bitString){
    int i = 0;
    while(num > 0){
        bitString[i] = num % 2;
        num = num / 2;
        i++;
    }
}

int getLastAddress(pBitString head){
    if(head == NULL){
        return -1;
    }
    pBitString temp = head;
    while(temp->next != NULL){
        temp = temp->next;
    }
    return temp->address;
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
    char *temp = str;
    while(*temp != '\0'){

        if(*temp != ' ' && *temp != '\t' && *temp != '\n'){
            *str = *temp;
            str++;
        }
        temp++;
    }
    *str = '\0';
}
//(*str >= 'a'&&*str <= 'z')||(*str >= 'A'&&*str <= 'Z')||(*str >= '@')||(*str >= '(')||(*str >= ')')||(*str >= '\n')

void writeFileDebug(pLine head, char *fileName){
    FILE *file = fopen(fileName, "w");
    pLine temp = head;
    while(temp != NULL) {
        if (temp->next == NULL) fprintf(file, "%s", temp->codeLine);
        else fprintf(file, "%s\n", temp->codeLine);
        temp = temp->next;
    }
}

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

pSymbleTable insertSymbleInQueue(pSymbleTable head, char *symble, int address){
    pSymbleTable newLine = (pSymbleTable) malloc(sizeof(struct SymbleTable));
    strcpy(newLine->symble, symble);
    newLine->address = address;
    newLine->next = NULL;
    if(head == NULL){
        return newLine;
    }
    pSymbleTable temp = head;
    while(temp->next != NULL){
        temp = temp->next;
    }
    temp->next = newLine;
    return head;
}

void removeComments(char *str){
    char *new = str;
    while(*new != '\0'){
        if(*new == '/' && *(new+1) == '/'){
            *str = '\0';
            break;
        }
        *str = *new;
        str++;
        new++;
    }
    *str = '\0';
}

int identifyInstruction(const char *inst){
    if (*inst == '(') return 0;
    if (*inst == '@') return 1;
    else return 2;
}

void printSymbleTable(pSymbleTable head){
    pSymbleTable temp = head;
    while(temp != NULL) {
        printf( "- %s - %d -\n", temp->symble, temp->address);
        temp = temp->next;
    }
}