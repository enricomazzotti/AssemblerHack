#include <stdio.h>
#include <string.h>
#include <malloc.h>

struct line {
    char codeLine[100];
    struct line* next;
};

typedef struct line* pline;

int main() {
    printf("Hello, World!\n");
    pline p = malloc(sizeof(struct line));

    //read from file
    FILE* f = fopen("input.txt", "r");
    if (f == NULL) {
        printf("Error opening file!\n");
        exit(1);
    }
    char lineaLetta[100];


    strcpy(p->codeLine, lineaLetta);
    return 0;
}
