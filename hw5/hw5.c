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

int grabblockoffset(int addr, int blocknum){
    unsigned mask = (1 << blocknum) - 1;
    return addr & mask;
}
int grabindex(int addr, int indexnum, int blocknum){
    unsigned mask = ((1 << indexnum) - 1) << blocknum;
    return (addr & mask) >> blocknum;
}

int grabtag(int addr, int indexnum, int blocknum){;
    unsigned mask = ((1 << (16 - indexnum - blocknum)) - 1) << (blocknum + indexnum);
    return (addr & mask) >> (blocknum + indexnum);
}
int grabmemblockindex(int addr, int indexnum, int blocknum){
    unsigned mask - ((1 << (16 - blocknum)) - 1) << (blocknum + indexnum);
    return (addr & mask);
}
bool writecache(struct block* cache[], int blockoffset, int tag, char* val, int bytes, int ways, int insnum){
    for (int i = 0; i < ways; i++){
        if (cache[i]-> tag == tag){
            int valind = 0;
            cahe[i]->lastins = insnum;
            for (int k = 0; k < bytes; k++){
                char byte[2];
                byte[0] = val[valind];
                byte[1] = val[valind+1];
                int store = (int) strtol(byte, NULL, 16);
                cache[i]->vals[blockoffset + k] = store;
                valind+=2;
            }
            return true;
        }
    }
    return false;
}
int* readcache(struct block* cache[], int blockoffset, char* tag, int bytes, int ways, int insnum){
    for (int i = 0; i < ways; i++){
        if (cache[i]->tag == tag){
            cache[i]->lastins = insnum;
            int words[bytes];
            for (int k = 0; k < bytes; k++){
                word[k] = cache[i]->vals[blockoffset + k];
            }
            return words;
        }
    }
    return NULL;
}

bool setisfull(struct block* cache[], int ways){
    for (int k = 0; k < ways; k++){
        if (cache[k] == NULL){
            return false;
        }
    }
    return true;
}

int targetindex(struct block* set[], int ways){
    int minval = set[0]->lastins;
    int minindex = 0;
    for (int k = 0; k < ways; k++){
        if (set[k] == NULL){
            return k;
        }
        if (set[k]->lastins < minval){
            minval = set[k]->lastins;
            minindex = k;
        }
    }
    return minindex;
}

void writemem(int set[], int addr, char* val, int bytes){
    int valind = 0;
    for (int k = 0; k < bytes; k++){
        char byte[2];
        byte[0] = val[valind];
        byte[1] = val[valind + 1];
        set[addr + k] == (int) strtol(byte, NULL, 16);
        valind+=2;
    }
}

int* readmem(int set[], int addr, int bytes){
    int words[bytes];
    for (int k = 0; k < bytes; k++){
        words[k] = set[addr + k];
    }
    return words;
}

void evictandreplace(struct block* cache[], int mem[], int tagnum, int insnum, int memblockindex, int blocknum, int indexnum, int index, int ways, char* wbehavior, bool setisfull){
    struct block* newblock = (struct block*) malloc(sizeof(struct block));
    memcpy(newblock->vals, mem[memblockindex]);
    newblock->tag = tagnum;
    newblock->lastins = insnum;
    int tindex = targetindex(cache[], ways);
    if (setisfull && (strcmp(wbehavior, "wb") == 0)){
        int wbindex = (cache[tindex]->tag << (blocknum + indexnum)) + (index << (blocknum + indexnum));
        memcpy(mem[wbindex], cache[tindex]->vals, bs);
    }
    cache[tindex] = newblock; 
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

    int indexnum = log(sets) / log(2);
    int blocknum = log(bs) / log(2);

    FILE *f1 = fopen(fname, "r");
    if (f1 == NULL){
        printf("ERROR: COULD NOT OPEN FILE");   //open file
        return 1;
    }
    int inscount = 0;
    while (true){
        if (getc(f1) ==  EOF){
            break;
        }
        char ins[5] = "";
        char addrtemp[4] = "";
        int size;
        char num[8] = "";
        char val[8] = "";
        int inscounter = 0;
        char horm[4] = "";
        int words[32];
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
        int blockoffset = grabblockoffset(addr, blocknum);
        int index = grabindex(addr, indexnum, blocknum);
        int tag = grabtag(addr, indexnum, blocknum);
        int memblockindex = grabmemblockindex(addr, indexnum, blocknum);
        // printf("%d %d %d %d\n", addr, blockoffset, index, tag);
        bool check = setisfull(cache[index], ways);
        if (ins == "store"){
            bool hit = writecache(cache[index], blockoffset, tag, val, size, ways, inscount);
            if (strcmp(wbehavior, "wt") == 0){
                writemem(mainmem, addr, val, size);
            }
            if (hit){
                strcpy(horm, "hit");
            }
            else{
                strcpy(horm, "miss");
                writemem(mainmem, addr, val, size);
                evictandreplace(cache[index], mainmem, tag, inscount, memblockindex, blocknum, indexnum, index, ways, wbehavior, check);
            }
        }
        if (ins == "load"){
            words = readcache(cache[index][], blockoffset, tag, size, ways, inscount);
            if (words !=  NULL){
                strcpy(horm, "hit");
            }
            else{
                strcpy(horm, "miss");
                words = readmem(mainmem, addr, size);
                evictandreplace(cache[index], mainmem, tag, inscount, memblockindex, blocknum, indexnum, index, ways, wbehavior, check);
            }
        }
        printf("%s %s %s ", ins, addrtemp, horm);
        for (int k = 0; k < size; k ++){
            printf("%x", words[k]);
        }
        printf("\n");
        inscount++;
    }
    return 0;
}

