#include<stdio.h>
#include<stdlib.h>

struct person {
    char name[30];
    struct person* a;
    struct person* b;
};

int main(int argc, char* argv[]){
        char* filename = argv[1];
        FILE *fp = fopen(filename, "r");
        if (fp == NULL){
            printf("ERROR: COULD NOT OPEN FILE");
            return 1;
        }
        int size = 0;
        char c;
        for (c=getc(fp); c != EOF; c = getc(fp)){
            if (c == '\n'){
                size++;
            }
        }
        char names[2 * size];
        printf("%d", size);
         
}