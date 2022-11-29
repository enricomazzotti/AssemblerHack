/**
 * @author:  Enirco Mazzotti (matricola: 0001071247)
 * @date:    16/11/2022
 * @note:    Progetto 5 - Laboratorio Nand2Tetris
 * @project: Assemblatore per il linguaggio Assembly Hack
 */

#include <stdio.h>
#include <string.h>
#include <malloc.h>

#include "parser.h"
#include "symbletable.h"


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



// Prototipi delle funzioni

//assemlatore.c
pLine readFile(char *fileName, pSymbleTable); // Legge il file e ritorna una lista di linee di codice lette
void writeFile(pBitString head, char *fileName); // Scrive il file di output
pBitString convertToBitString(pLine,pSymbleTable symbleTable); // Converte la lista di linee di codice in una lista di stringhe binarie (lingiaggio macchina)
void convertAinstruction(char *line, char *bitString); // Converte una istruzione A in una stringa binaria
int convertCinstruction(char *line, char *bitString); // Converte una istruzione C in una stringa binaria
int isEligibleA(char *str);
int getLastAddress(pBitString head); // Ritorna l'ultimo indirizzo utilizzato
pLine insertLineInQueue(pLine head, char *line); // Inserisce una nuova linea di codice in coda alla lista
pBitString insertBitStringInQueue(pBitString head, char *line); // Inserisce una nuova stringa binaria in coda alla lista



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


    pSymbleTable symbleTable = initSymbleTable();

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
    // Combina con estensione ext
    const char ext[] = ".hack";
    const size_t ext_len = strlen(ext);
    char *res = malloc(sizeof(char) * (i + ext_len + 1));
    strcpy(strncpy(res, str, i) + i, ext);
    return res;
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

        if (*line != '\0' ) {
            // identifica l'istruzione
            if(identifyInstruction(line)==0) {
                removeBrackets(line);

                searchSymble(symbleTable,line);
                insertSymbleInQueue(symbleTable,line,contatore);
                //printf("Label %s\n", line);
                //printSymbleTable(symbleTable);
            } else {

                head = insertLineInQueue(head, line);
                contatore++;
            }

        }

    }
    return head;
}

// stringa deve essere lunga 12


int convertCinstruction(char *line, char *bitString){
    if (strlen(line) < 3 || strlen(line) > 12) return 0;

    int translated = 1;

    char dest[5];
    char comp[4];
    char jump[5];
    getDest(line,dest);
    getComp(line,comp);
    getJump(line,jump);
    char tdest[4];
    char tcomp[8];
    char tjump[4];

    //translate dest
    if (strcmp(dest, "null") == 0) {
        strcpy(tdest, "000");
    }
    else if (strcmp(dest, "M") == 0) {
        strcpy(tdest, "001");
    }
    else if (strcmp(dest, "D") == 0) {
        strcpy(tdest, "010");
    }
    else if (strcmp(dest, "MD") == 0) {
        strcpy(tdest, "011");
    }
    else if (strcmp(dest, "A") == 0) {
        strcpy(tdest, "100");
    }
    else if (strcmp(dest, "AM") == 0) {
        strcpy(tdest, "101");
    }
    else if (strcmp(dest, "AD") == 0) {
        strcpy(tdest, "110");
    }
    else if (strcmp(dest, "AMD") == 0) {
        strcpy(tdest, "111");
    }
    else {
        translated = 0;
    }


    //translate comp
    if (strcmp(comp, "0") == 0) {
        strcpy(tcomp, "0101010");
    }
    else if (strcmp(comp, "1") == 0) {
        strcpy(tcomp, "0111111");
    }
    else if (strcmp(comp, "-1") == 0) {
        strcpy(tcomp, "0111010");
    }
    else if (strcmp(comp, "D") == 0) {
        strcpy(tcomp, "0001100");
    }
    else if (strcmp(comp, "A") == 0) {
        strcpy(tcomp, "0110000");
    }
    else if (strcmp(comp, "!D") == 0) {
        strcpy(tcomp, "0001101");
    }
    else if (strcmp(comp, "!A") == 0) {
        strcpy(tcomp, "0110001");
    }
    else if (strcmp(comp, "-D") == 0) {
        strcpy(tcomp, "0001111");
    }
    else if (strcmp(comp, "-A") == 0) {
        strcpy(tcomp, "0110011");
    }
    else if (strcmp(comp, "D+1") == 0) {
        strcpy(tcomp, "0011111");
    }
    else if (strcmp(comp, "A+1") == 0) {
        strcpy(tcomp, "0110111");
    }
    else if (strcmp(comp, "D-1") == 0) {
        strcpy(tcomp, "0001110");
    }
    else if (strcmp(comp, "A-1") == 0) {
        strcpy(tcomp, "0110010");
    }
    else if (strcmp(comp, "D+A") == 0 || strcmp(comp, "A+D") == 0) {
        strcpy(tcomp, "0000010");
    }
    else if (strcmp(comp, "D-A") == 0) {
        strcpy(tcomp, "0010011");
    }
    else if (strcmp(comp, "A-D") == 0) {
        strcpy(tcomp, "0000111");
    }
    else if (strcmp(comp, "D&A") == 0 || strcmp(comp, "A&D") == 0) {
        strcpy(tcomp, "0000000");
    }
    else if (strcmp(comp, "D|A") == 0 || strcmp(comp, "A|D") == 0) {
        strcpy(tcomp, "0010101");
    }
    else if (strcmp(comp, "M") == 0) {
        strcpy(tcomp, "1110000");
    }
    else if (strcmp(comp, "!M") == 0) {
        strcpy(tcomp, "1110001");
    }
    else if (strcmp(comp, "-M") == 0) {
        strcpy(tcomp, "1110011");
    }
    else if (strcmp(comp, "M+1") == 0) {
        strcpy(tcomp, "1110111");
    }
    else if (strcmp(comp, "M-1") == 0) {
        strcpy(tcomp, "1110010");
    }
    else if (strcmp(comp, "D+M") == 0 || strcmp(comp, "M+D") == 0) {
        strcpy(tcomp, "1000010");
    }
    else if (strcmp(comp, "D-M") == 0) {
        strcpy(tcomp, "1010011");
    }
    else if (strcmp(comp, "M-D") == 0) {
        strcpy(tcomp, "1000111");
    }
    else if (strcmp(comp, "D&M") == 0 || strcmp(comp, "M&D") == 0) {
        strcpy(tcomp, "1000000");
    }
    else if (strcmp(comp, "D|M") == 0 || strcmp(comp, "M|D") == 0) {
        strcpy(tcomp, "1010101");
    }
    else {
        translated = 0;
    }


    //translate jump
    if (strcmp(jump, "null") == 0) {
        strcpy(tjump, "000");
    }
    else if (strcmp(jump, "JGT") == 0) {
        strcpy(tjump, "001");
    }
    else if (strcmp(jump, "JEQ") == 0) {
        strcpy(tjump, "010");
    }
    else if (strcmp(jump, "JGE") == 0) {
        strcpy(tjump, "011");
    }
    else if (strcmp(jump, "JLT") == 0) {
        strcpy(tjump, "100");
    }
    else if (strcmp(jump, "JNE") == 0) {
        strcpy(tjump, "101");
    }
    else if (strcmp(jump, "JLE") == 0) {
        strcpy(tjump, "110");
    }
    else if (strcmp(jump, "JMP") == 0) {
        strcpy(tjump, "111");
    }
    else {
        translated = 0;
    }

    strcpy(bitString, "111");
    strcat(bitString, tcomp);
    strcat(bitString, tdest);
    strcat(bitString, tjump);
    return translated;
}



int isEligibleA(char *str){
    int isNumber = 0;
    int isLabel = 0;
    if (*str=='@'){
        str++;
        if (*str == '$'|| *str == '.'|| *str == '_' || (*str >= 'A' && *str <= 'Z') || (*str >= 'a' && *str <= 'z')){
            isLabel = 1;
            str++;
        } else if (*str >= '0' && *str <= '9'){
            isNumber = 1;
            str++;
        } else {
            return 0;
        }

        if (isNumber==1){
            while (*str != '\0'){
                if (*str >= '0' && *str <= '9'){
                    str++;
                } else {
                    return 0;
                }
            }
        }

        if (isLabel==1){
            while (*str != '\0'){
                if (*str == '$'|| *str == '.'|| *str == '_' || (*str >= 'A' && *str <= 'Z') || (*str >= 'a' && *str <= 'z') || (*str >= '0' && *str <= '9')){
                    str++;
                } else {
                    return 0;
                }
            }

        }

    } else {
        return 0;
    }
    return 1;
}

pBitString convertToBitString(pLine headLine,pSymbleTable symbleTable){
    pBitString head = NULL;
    int contatore = 16;

    while (headLine != NULL){
        if  (identifyInstruction(headLine->codeLine) == 1){
            if (isEligibleA(headLine->codeLine)==1){  // se è una variabile o un'etichetta

                char bitString[17];
                char *temp = headLine->codeLine+1;

                if (!(headLine->codeLine[1] >= '0' && headLine->codeLine[1] <= '9')){  // se è un'etichetta

                    // controlla se è in symble table
                    // se non c'è aggiungilo con il valore del contatore
                    int val= searchSymble(symbleTable,temp);
                    if (val==-1){
                        // inserisci il simbolo in tabella
                        insertSymbleInQueue(symbleTable,temp,contatore);
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
                printf("Errore: %s istruzione A valida", headLine->codeLine);
            }




        } else{
            char bitString[17];
            if (convertCinstruction(headLine->codeLine, bitString)==1){
                head = insertBitStringInQueue(head, bitString);
            } else {
                printf("Errore: %s istruzione C valida", headLine->codeLine);
            }
        }
        headLine = headLine->next;
    }



    return head;
}






void convertAinstruction(char *line, char *bitString){
    if (*line== '@'){
        line++;
        int num = parseint(line);
        base10ToBase2on16bit(num, bitString);
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













