#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include <stdbool.h>

int bs;
int indexnum;
int blocknum;

struct block{
        char vals[64];
        int tag;      //block struct
        int lastins;
    };

int grabblockoffset(int addr, int blocksize){
    int blocknum = log(blocksize) / log(2);
    unsigned mask = (1 << blocknum) - 1;
    return addr & mask;
}

int main(int argc, char* argv[]){
    char* fname = argv[1];
    int size = atoi(argv[2]);
    int ways = atoi(argv[3]);           //extract args
    char* wbehavior = argv[4];
    int bs = atoi(argv[5]);

    int num_frames = (size * 1024) / bs;
    int sets = num_frames / ways;       //dimensions calc

    struct block* cache[sets][ways];            //creating cache and main memory with proper dimensions
    char mainmem[65536];


    FILE *f1 = fopen(fname, "r");
    if (f1 == NULL){
        printf("ERROR: COULD NOT OPEN FILE");   //open file
        return 1;
    }
    while (true){
        char ins[5] = "";
        char addrtemp[4] = "";
        int size;
        char num[8] = "";
        char val[8] = "";
        int inscounter = 0;
        char horm[4] = "";
        char word[16] = "";
        int i = 0;
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
            addrtemp[i] = c;
            i++;
        }
        for (char c=getc(f1); c != EOF; c = getc(f1)){
                if (c == ' '){
                    i = 0;
                    break;
                }
            size = c - '0';
            i++;
        }
        for (char c=getc(f1); c != EOF; c = getc(f1)){
                if (c == ' ' || c == '\n'){
                    i = 0;
                    break;
                }
            val[i] = c;
            i++;
        }
        // printf("%s %s %d %s\n", ins, addr, size, val);
        int addr = (int) strtol(addrtemp, NULL, 16);
        // char charbin[16] = hextobin(addr);
        int blockoffset = grabblockoffset(addr, bs);
        printf("%d %d\n", addr, blockoffset);
        break;
        // int index = grabindex(charbin, sets, bloksize);
        // int memindex = grabmemindex(charbin, bs);
        // char tag[16] = grabtag(charbin, sets, bs);


        // if (ins == "store"){
        //     bool hit = writecache(cache[index][], blockoffset, tag, val, size, ways);
        //     if (strcmp(wbehavior, "wt") == 0){
        //         int j = 0;
        //         for (int k = 0; k < bytes; k+=2){
        //             mainmem[memindex]->vals[blockoffset + j][0] = val[k];
        //             mainmem[memindex]->vals[blockoffset + j][1] = val[k+1];
        //             j++;
        //         }
        //     }
        //     if (hit){
        //         strcpy(horm, "HIT");
        //     }
        //     else{
        //         strcpy(horm, "MISS");
        //         if (setisfull(cache[index][], ways)){
        //             int indmin = minindex(cache[index][], ways);
        //             if (strcmp(wbehavior, "wb")){
        //                 int repindex = bindtodec(tag) * 16 + index;
        //                 memcpy(mainmem + repindex, cache[index][indmin]->vals)
        //             }
        //             int j = 0;
        //             cahe[index][indmin]->lastins = insnum;
        //             for (int k = 0; k < bytes; k+=2){
        //                 cache[index][indmin]->vals[blockoffset + j][0] = val[k];
        //                 cache[index][indmin]->vals[blockoffset + j][1] = val[k+1];
        //                 j++;
        //             }
        //             cache[index][indmin]->tag = tag;
        //         }
        //     }
        // }
        // if (ins == "load"){
        //     word = readcache(cache[index][], blockoffet, tag, size, ways);
        //     if (strcmp(read, "") != 0){
        //         strcpy(horm, "HIT");
        //     }
        //     else{
        //         strcpy(horm, "MISS");
        //         struct block* newcache[index];
        //         for (int i = 0; i < ways; i++){
        //             if (i == 0){
        //                 newcache[k] = mainmem[memindex];
        //             }
        //             else{
        //                 newcache[k] = cache[index][k];
        //             }
        //         }
        //         cache[index] = newcache[k];
        //     }
        // }
    
    }
    return 0;
}

// bool writecache(struct block* cache[], int blockos, char* tag, char* val, int bytes, int ways, int insnum){
//     for (int i = 0; i < ways; i++){
//         if (strcmp(cache[i]->tag, tag) == 0){
//             int j = 0;
//             cahe[i]->lastins = insnum;
//             for (int k = 0; k < bytes; k+=2){
//                 cache[i]->vals[blockos + j][0] = val[k];
//                 cache[i]->vals[blockos + j][1] = val[k+1];
//                 j++;
//             }
//             return true;
//         }
//     }

//     return false;
// }
// char* readcache(struct block* cache[], int blockos, char* tag, int bytes, int ways, int insnum){
//     for (int i = 0; i < ways; i++){
//         if (strcmp(cache[i]->tag, tag) == 0){
//             cache[i]->lastins = insnum;
//             char word[16] = "";
//             int j = 0;
//             for (int k = 0; k < bytes * 2; k+=2){
//                 word[k] = cache[i]->vals[blockos + j][0];
//                 word[k+1] = cache[i]->vals[blockos + j][1];
//             }
//             return word;
//         }
//     }
//     return "";
// }

// char* hextobin(char* hex){
//     char bin[30] = "";
//     int i = 0;
//     while(hex[i]){
//         switch (hex[i]){
//             case '0':
//                 bin[i] = 0; bin[i+1] = 0; bin[i+2] = 0; bin[i+3] = 0;
//                 break;
//             case '1':
//                 bin[i] = 0; bin[i+1] = 0; bin[i+2] = 0; bin[i+3] = 1;
//                 break;
//             case '2':
//                 bin[i] = 0; bin[i+1] = 0; bin[i+2] = 1; bin[i+3] = 0;
//                 break;
//             case '3':
//                 bin[i] = 0; bin[i+1] = 0; bin[i+2] = 1; bin[i+3] = 1;
//                 break;
//             case '4':
//                 bin[i] = 0; bin[i+1] = 1; bin[i+2] = 0; bin[i+3] = 0;
//                 break;
//             case '5':
//                 bin[i] = 0; bin[i+1] = 1; bin[i+2] = 0; bin[i+3] = 1;
//                 break;
//             case '6':
//                 bin[i] = 0; bin[i+1] = 1; bin[i+2] = 1; bin[i+3] = 0;
//                 break;
//             case '7':
//                 bin[i] = 0; bin[i+1] = 1; bin[i+2] = 1; bin[i+3] = 1;
//                 break;
//             case '8':
//                 bin[i] = 1; bin[i+1] = 0; bin[i+2] = 0; bin[i+3] = 0;
//                 break;
//             case '9':
//                 bin[i] = 1; bin[i+1] = 0; bin[i+2] = 0; bin[i+3] = 1;
//                 break;
//             case 'a':
//                 bin[i] = 1; bin[i+1] = 0; bin[i+2] = 1; bin[i+3] = 0;
//                 break;
//             case 'b':
//                 bin[i] = 1; bin[i+1] = 0; bin[i+2] = 1; bin[i+3] = 1;
//                 break;
//             case 'c':
//                 bin[i] = 1; bin[i+1] = 1; bin[i+2] = 0; bin[i+3] = 0;
//                 break;
//             case 'd':
//                 bin[i] = 1; bin[i+1] = 1; bin[i+2] = 0; bin[i+3] = 1;
//                 break;
//             case 'e':
//                 bin[i] = 1; bin[i+1] = 1; bin[i+2] = 1; bin[i+3] = 0;
//                 break;
//             case 'f':
//                 bin[i] = 1; bin[i+1] = 1; bin[i+2] = 1; bin[i+3] = 1;
//                 break;
//             default:
//                 printf("\nInvalid hexadecimal digit %c", hex[i]);
//         }
//         i+=4;
//     }
//     return bin;
// }
// int bintodec(char* bin){
//     int x = 0;
//     for (int i = 0; i < 16; i++){
//         int a =  bin[i] - '0';
//         x += a * (int) pow(2.0, (double) i);
//     }
//     return x;
// }


// int grabindex(char* bin, int sets, int blocksize){
//     int indexnum = log(sets) / log(2);
//     int blocknum = log(blocksize) / log(2);
//     char string[indexnum];
//     for (int = blocknum; k < indexnum + blocknum; k++){
//         string[k] = bin[k];
//     }
//     return bintodec(string);
// }

// int grabmemindex(char* bin, int blocksize){
//     int blocknum = log(bs) / log(2);
//     char string[16 - blocknum];
//     for (int k = blocknum; k < 16; k++){
//         string[k] = bin[k];
//     }
//     return bintodec(string);
// }

// char* grabtag(char* bin, int sets, int blocksize){
//     int indexnum = log(sets) / log(2);
//     int blocknum = log(bs) / log(2);
//     char string[16 - start];
//     for (int k = indexnum + blocknum; k < 16; k++){
//         string[k] = bin[k];
//     }
//     return string;
// }

// bool setisfull(struct block* cache[], int ways){
//     for (int k = 0; k < ways; k++){
//         if (cache[k] == NULL){
//             return false;
//         }
//     }
//     return true;
// }

// int minindex(struct block* set[], int ways){
//     int min = set[0]->lastins;
//     for (int k = 1; k < ways; k++){
//         if (set[k]->lastins < min){
//             min = set[k]->lastins;
//         }
//     }
//     return min;
// }