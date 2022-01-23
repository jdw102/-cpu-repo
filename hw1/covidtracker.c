#include<stdio.h>
#include<stdlib.h>

typedef struct person {
    char name[];
    struct* person a;
    struct* person b;
}person_t

int main(int argc, char* argv[]){
        char* filename = arv[1];
        FILE *fp = fopen(filename, "r");
        if (fp == NULL){
            printf("ERROR: COULD NOT OPEN FILE");
            return 1;
        }
        int size = 0;
        for (c=getc(fp; c != EOF; c = getc(fp)){
            if (c == '\n'){
                size++;
            }
        }
        char names[2 * size];
        printf("%d", size);
         
}