/**
 * @author:  Enirco Mazzotti (matricola: 0001071247)
 * @date:    16/11/2022
 * @note:    file sorgente che implementa le funzioni per manipolare le stringhe
 * @project: Assemblatore per il linguaggio Assembly Hack
 * @file:    parser.c
 */

#include "parser.h"


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

int parseint(const char *str){
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
        bitString[i] = num % 2 + '0';
        num = num / 2;
        i--;
    } while (i >= 0){
        bitString[i] = '0';
        i--;
    }
}

int identifyInstruction(const char *inst){
    if (*inst == '(') return 0;
    if (*inst == '@') return 1;
    else return 2;
}



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

void convertIntToString(char *str, int num){
    int i = 0;
    while(num > 0){
        str[i] = num % 10 + '0';
        num = num / 10;
        i++;
    }
    str[i] = '\0';
    reverseString(str);
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

void getDest(char *str,char *dest){
    if (strchr(str, '=') == NULL) {
        strcpy(dest, "null");
        return;
    }
    int i = 0;
    while ( str[i] != '=' ){
        dest[i] = str[i];
        i++;
    }
    dest[i] = '\0';
}
void getComp(char *str,char *comp){
    if (strchr(str, '=') == NULL && strchr(str, ';') == NULL) {
        strcpy(comp, str);
    }
    else if (strchr(str, '=') == NULL){
        int i = 0;
        while ( str[i] != ';' ){
            comp[i] = str[i];
            i++;
        }
        comp[i] = '\0';
    }
    else if (strchr(str, ';') == NULL){
        int i = 0;
        while ( str[i] != '=' ){
            i++;
        }
        i++;
        int j = 0;
        while ( str[i] != '\0' ){
            comp[j] = str[i];
            i++;
            j++;
        }
        comp[j] = '\0';
    }
    else {
        int i = 0;
        while ( str[i] != '=' ){
            i++;
        }
        i++;
        int j = 0;
        while ( str[i] != ';' ){
            comp[j] = str[i];
            i++;
            j++;
        }
        comp[j] = '\0';
    }
}
void getJump(char *str,char *jump){

    if (strchr(str, ';') == NULL) {
        strcpy(jump, "null");
        return;
    }
    int i = 0;
    while ( str[i] != ';' ){
        i++;
    }
    i++;
    int j = 0;
    while ( str[i] != '\0' ){
        jump[j] = str[i];
        i++;
        j++;
    }
    jump[j] = '\0';

}