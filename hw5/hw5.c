#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include <stdbool.h>

int bs;
int indexnum;
int blocknum;

struct block{
        char vals[64][2];
        char tag[16];      //block struct
    };



int main(int argc, char* argv[]){
    char* fname = argv[1];
    int size = atoi(argv[2]);
    int ways = atoi(argv[3]);           //extract args
    char* wbehavior = argv[4];
    int bs = atoi(argv[5]); 

    int num_frames = (size * 1024) / bs;
    int sets = num_frames / ways;       //dimensions calc
    int indexnum = log(sets) / log(2);
    int blocknum = log(bs) / log(2);

    struct block* cache[sets][ways];            //creating cache and main memory with proper dimensions
    struct block* mainmem[65536/bs];

    for (int k = 0; k < 65536/bs; k++){
        mainmem[k] = (struct block*) malloc(sizeof(struct block));
    }

    FILE *f1 = fopen(fname, "r");
    if (f1 == NULL){
        printf("ERROR: COULD NOT OPEN FILE");   //open file
        return 1;
    }
    while (true){
        char ins[5] = "";
        char addr[4] = "";
        int size;
        char val[8] = "";
        int i = 0;
        char horm[4] = "";
        char word[16] = "";
        for (char c=getc(f1); c != EOF; c = getc(f1)){
                if (c == ' '){
                    i = 0;
                    break;
                }
            ins[i] = c;
            i++;
        }
        for (char c=getc(f1); c != EOF; c = getc(f1)){
                if (c == ' '){
                    i = 0;
                    break;
                }
            addr[i] = c;
            i++;
        }
        for (char c=getc(f1); c != EOF; c = getc(f1)){
                if (c == ' '){
                    i = 0;
                    break;
                }
            size = (int) c;
            i++;
        }
        for (char c=getc(f1); c != EOF; c = getc(f1)){
                if (c == ' '){
                    i = 0;
                    break;
                }
            val[i] = c;
            i++;
        }
        printf("%s %s %d %s\n", ins, addr, size, val);

        if (ins == "store"){

        }
        if (ins == "load"){

        }
    }


}

bool writecache(struct block* cache[], int blockos, char* tag, char* val, int bytes, int ways){
    for (int i = 0; i < ways; i++){
        if (strcmp(cache[i]->tag, tag) == 0){
            int j = 0;
            for (int k = 0; k < bytes; k+=2){
                cache[i]->vals[blockos + j][0] = val[k];
                cache[i]->vals[blockos + j][1] = val[k+1];
                j++;
            }
            return true;
        }
    }
    return false;
}
char* readcache(struct block* cache[], int blockos, char* tag, int bytes, int ways){
    for (int i = 0; i < ways; i++){
        if (strcmp(cache[i]->tag, tag) == 0){
            char word[16] = "";
            int j = 0;
            for (int k = 0; k < bytes * 2; k+=2){
                word[k] = cache[i]->vals[blockos + j][0];
                word[k+1] = cache[i]->vals[blockos + j][1];
            }
            return word;
        }
    }
    return "";
}

void blockcpy(struct block* b1, struct block* b2){

}


char* hextobin(char* hex){
    char bin[30] = "";
    int i = 0;
    while(hex[i]){
        switch (hex[i]){
            case '0':
                bin[i] = 0; bin[i+1] = 0; bin[i+2] = 0; bin[i+3] = 0;
                break;
            case '1':
                bin[i] = 0; bin[i+1] = 0; bin[i+2] = 0; bin[i+3] = 1;
                break;
            case '2':
                bin[i] = 0; bin[i+1] = 0; bin[i+2] = 1; bin[i+3] = 0;
                break;
            case '3':
                bin[i] = 0; bin[i+1] = 0; bin[i+2] = 1; bin[i+3] = 1;
                break;
            case '4':
                bin[i] = 0; bin[i+1] = 1; bin[i+2] = 0; bin[i+3] = 0;
                break;
            case '5':
                bin[i] = 0; bin[i+1] = 1; bin[i+2] = 0; bin[i+3] = 1;
                break;
            case '6':
                bin[i] = 0; bin[i+1] = 1; bin[i+2] = 1; bin[i+3] = 0;
                break;
            case '7':
                bin[i] = 0; bin[i+1] = 1; bin[i+2] = 1; bin[i+3] = 1;
                break;
            case '8':
                bin[i] = 1; bin[i+1] = 0; bin[i+2] = 0; bin[i+3] = 0;
                break;
            case '9':
                bin[i] = 1; bin[i+1] = 0; bin[i+2] = 0; bin[i+3] = 1;
                break;
            case 'a':
                bin[i] = 1; bin[i+1] = 0; bin[i+2] = 1; bin[i+3] = 0;
                break;
            case 'b':
                bin[i] = 1; bin[i+1] = 0; bin[i+2] = 1; bin[i+3] = 1;
                break;
            case 'c':
                bin[i] = 1; bin[i+1] = 1; bin[i+2] = 0; bin[i+3] = 0;
                break;
            case 'd':
                bin[i] = 1; bin[i+1] = 1; bin[i+2] = 0; bin[i+3] = 1;
                break;
            case 'e':
                bin[i] = 1; bin[i+1] = 1; bin[i+2] = 1; bin[i+3] = 0;
                break;
            case 'f':
                bin[i] = 1; bin[i+1] = 1; bin[i+2] = 1; bin[i+3] = 1;
                break;
            default:
                printf("\nInvalid hexadecimal digit %c", hex[i]);
        }
        i+=4;
    }
    return bin;
}
int bintodec(char* bin){
    int x = 0;
    for (int i = 0; i < 16; i++){
        int a = (int) bin[i];
        x += a * (int) pow(2.0, (double) i);
    }
    return x;
}
