/**
 * @author:  Enirco Mazzotti (matricola: 0001071247)
 * @date:    16/11/2022
 * @note:    Progetto 5 - Laboratorio Nand2Tetris
 * @project: Assemblatore per il linguaggio Assembly Hack
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <stdbool.h>


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

struct SymbleTable {
    int address;
    char symble[100];
    struct SymbleTable* next;
};

typedef struct SymbleTable* pSymbleTable;
// Prototipi delle funzioni

pLine readFile(char *fileName, pSymbleTable); // Legge il file e ritorna una lista di linee di codice lette

pBitString convertToBitString(pLine,pSymbleTable symbleTable); // Converte la lista di linee di codice in una lista di stringhe binarie (lingiaggio macchina)

void writeFile(pBitString head, char *fileName); // Scrive il file di output

pLine insertLineInQueue(pLine head, char *line); // Inserisce una nuova linea di codice in coda alla lista

pBitString insertBitStringInQueue(pBitString head, char *line); // Inserisce una nuova stringa binaria in coda alla lista

void trimAll(char *str); // Rimuove gli spazi bianchi e le tabulazioni da una stringa

void removeComments(char *str); // Rimuove i commenti da una stringa

void writeFileDebug(pLine head, char *fileName); // Scrive il file di debug

void convertAinstruction(char *line, char *bitString); // Converte una istruzione A in una stringa binaria

void convertCinstruction(char *line, char *bitString); // Converte una istruzione C in una stringa binaria

int parseint(char *str); // Converte una stringa in un intero

void base10ToBase2on16bit(int num, char *bitString); // Converte un intero in una stringa binaria

pSymbleTable initSymbleTable();

pSymbleTable insertSymbleInQueue(pSymbleTable head, char *symble, int address);

//int getSymbolAddress(char *symbol, pBitString head); // Ritorna l'indirizzo di un simbolo

int getLastAddress(pBitString head); // Ritorna l'ultimo indirizzo utilizzato

int identifyInstruction(const char *inst); // Ritorna 0 se label, 1 se a inst, 2 c inst

void removeBrackets(char*);

void printSymbleTable(pSymbleTable head);

void convertIntToString(char *str, int num);

void reverseString(char *str);

bool isEligibleA(char *str);

int searchSymble(pSymbleTable , char*);

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
    pBitString machineLanguageCode = convertToBitString(code,symbleTable);
    //writeFileDebug(code, "debug.asm");
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

//TODO: da controllare
void convertCinstruction(char *line, char *bitString){
    char *dest = strtok(line, "=");
    char *comp = strtok(NULL, ";");
    char *jump = strtok(NULL, ";");
    if(dest == NULL){
        dest = "null";
    }
    if(jump == NULL){
        jump = "null";
    }
    strcpy(bitString, "111");
    if(strcmp(dest, "null") == 0){
        strcat(bitString, "000");
    } else if(strcmp(dest, "M") == 0){
        strcat(bitString, "001");
    } else if(strcmp(dest, "D") == 0){
        strcat(bitString, "010");
    } else if(strcmp(dest, "MD") == 0){
        strcat(bitString, "011");
    } else if(strcmp(dest, "A") == 0){
        strcat(bitString, "100");
    } else if(strcmp(dest, "AM") == 0){
        strcat(bitString, "101");
    } else if(strcmp(dest, "AD") == 0){
        strcat(bitString, "110");
    } else if(strcmp(dest, "AMD") == 0){
        strcat(bitString, "111");
    }
    if(strcmp(comp, "0") == 0){
        strcat(bitString, "0101010");
    } else if(strcmp(comp, "1") == 0){
        strcat(bitString, "0111111");
    } else if(strcmp(comp, "-1") == 0){
        strcat(bitString, "0111010");
    } else if(strcmp(comp, "D") == 0){
        strcat(bitString, "0001100");
    } else if(strcmp(comp, "A") == 0){
        strcat(bitString, "0110000");
    } else if(strcmp(comp, "!D") == 0){
        strcat(bitString, "0001101");
    } else if(strcmp(comp, "!A") == 0){
        strcat(bitString, "0110001");
    } else if(strcmp(comp, "-D") == 0){
        strcat(bitString, "0001111");
    } else if(strcmp(comp, "-A") == 0){
        strcat(bitString, "0110011");
    } else if(strcmp(comp, "D+1") == 0){
        strcat(bitString, "0011111");
    } else if(strcmp(comp, "A+1") == 0){

    }
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

bool isEligibleA(char *str){
    bool isNumber = false;
    bool isLabel = false;
    if (*str=='@'){
        str++;
        if (*str == '$'|| *str == '.'|| *str == '_' || (*str >= 'A' && *str <= 'Z') || (*str >= 'a' && *str <= 'z')){
            isLabel = true;
            str++;
        } else if (*str >= '0' && *str <= '9'){
            isNumber = true;
            str++;
        } else {
            return false;
        }

        if (isNumber){
            while (*str != '\0'){
                if (*str >= '0' && *str <= '9'){
                    str++;
                } else {
                    return false;
                }
            }
        }

        if (isLabel){
            while (*str != '\0'){
                if (*str == '$'|| *str == '.'|| *str == '_' || (*str >= 'A' && *str <= 'Z') || (*str >= 'a' && *str <= 'z') || (*str >= '0' && *str <= '9')){
                    str++;
                } else {
                    return false;
                }
            }

        }

    } else {
        return false;
    }
    return true;
}

pBitString convertToBitString(pLine headLine,pSymbleTable symbleTable){
    // TODO: Implementare la funzione che converte la lista di linee di codice in una lista di stringhe binarie
    pBitString head = NULL;
    pLine temp = headLine;
    int contatore = 16;

    while (headLine != NULL){
        if  (identifyInstruction(headLine->codeLine) == 1){
            if (isEligibleA(headLine->codeLine)){
                // TODO: questa parte va cambiata totalmente
                // se è una variabile o un'etichetta

                char bitString[17];
                char *temp = headLine->codeLine+1;

                if (!(headLine->codeLine[1] >= '0' && headLine->codeLine[1] <= '9')){
                    // se è un'etichetta
                    // controlla se è in symble table
                    // se non c'è aggiungilo con un progressivo che parte da 16
                    int val= searchSymble(symbleTable,temp);
                    if (val==-1){
                        // inserisci il simbolo in tabella
                        char app[17];
                        convertIntToString(temp,contatore);
                        app[0] = '@';
                        app[1] = '\0';
                        strcat(app, temp);

                        convertAinstruction(app, bitString);
                        head = insertBitStringInQueue(head, bitString);
                        contatore++;
                    }else{
                        char app[17];
                        convertIntToString(temp,val);
                        app[0] = '@';
                        app[1] = '\0';
                        strcat(app, temp);

                        convertAinstruction(app, bitString);
                        head = insertBitStringInQueue(head, bitString);
                    }

                }else{

                    convertAinstruction(headLine->codeLine, bitString);
                    head = insertBitStringInQueue(head, bitString);
                }
            } else {
                printf("Errore: %s non è un'istruzione A valida", headLine->codeLine);
            }




        } else{
            char bitString[17];
            // TODO: implementare la funzione che converte una istruzione C in una stringa binaria
            strcpy(bitString, "c instruction");
            //convertCinstruction(headLine->codeLine, bitString);
            head = insertBitStringInQueue(head, bitString);
        }
        headLine = headLine->next;
    }


    return head;
}

int searchSymble(pSymbleTable head, char* symble){
    while (head != NULL){
        if (strcmp(head->symble,symble) == 0){
            return head->address;
        }
        head = head->next;
    }
    return -1;
}

void reverseString(char *str){
    int l = strlen(str);
    char app[l];
    for (int i = 0; i < l; i++) {
        app[i] = str[i];
    }
    for (int i = 0; i < l; i++) {
        str[i] = app[l-i-1];
    }
}

// todo: controlla questa funzione
void convertIntToString(char *str, int num){
    int i = 0;
    while(num > 0){
        str[i] = (num % 10) + '0';
        num = num / 10;
        i++;
    }
    str[i] = '\0';
    reverseString(str);
}

void convertAinstruction(char *line, char *bitString){
    if (*line== '@'){
        line++;
        int num = parseint(line);
        base10ToBase2on16bit(num, bitString);
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

void base10ToBase2on16bit(int num, char *bitString){
    bitString[16] = '\0';
    int i = 15;
    while (num > 0){
        bitString[i] = (num % 2) + '0';
        num = num / 2;
        i--;
    } while (i >= 0){
        bitString[i] = '0';
        i--;
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
        fprintf(file, "%s\n", temp->machineLangaugeLine);
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