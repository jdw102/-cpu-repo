#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include <stdbool.h>

int bs;
int indexnum;
int blocknum;

struct block{
        int vals[64];
        int tag;      //block struct
        int lastins;
        int valid;
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
    unsigned mask = ((1 << (16 - blocknum)) - 1) << (blocknum);
    return (addr & mask);
}
bool writecache(struct block* cache, int blockoffset, int tag, char* val, int bytes, int ways, int insnum){
    for (int i = 0; i < ways; i++){
        if (cache[i].tag == tag && cache[i].valid == 1){
            int valind = 0;
            cache[i].lastins = insnum;
            for (int k = 0; k < bytes; k++){
                char byte[2];
                byte[0] = val[valind];
                byte[1] = val[valind+1];
                int store = (int) strtol(byte, NULL, 16);
                cache[i].vals[blockoffset + k] = store;
                valind+=2;
            }
            return true;
        }
    }
    return false;
}
bool readcache(struct block* cache, int blockoffset, int tag, int bytes, int ways, int insnum, int* words){
    for (int i = 0; i < ways; i++){
        if (cache[i].tag == tag && cache[i].valid == 1){
            cache[i].lastins = insnum;
            for (int k = 0; k < bytes; k++){
                 words[k] = cache[i].vals[blockoffset + k];
            }
            return true;
        }
    }
    return false;
}

bool setisfull(struct block* cache, int ways){
    for (int k = 0; k < ways; k++){
        if (cache[k].valid == 0){
            return false;
        }
    }
    return true;
}

int targetindex(struct block* set, int ways){
    int minval = set[0].lastins;
    int minindex = 0;
    for (int k = 0; k < ways; k++){
        if (set[k].valid == 0){
            return k;
        }
        if (set[k].lastins < minval){
            minval = set[k].lastins;
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
        set[addr + k] = (int) strtol(byte, NULL, 16);
        valind+=2;
    }
}

int* readmem(int set[], int addr, int bytes, int* words){
    for (int k = 0; k < bytes; k++){
        *(words  + k) = set[addr + k];
    }
    return words;
}

void evictandreplace(struct block* cache, int mem[], int tagnum, int insnum, int memblockindex, int blocknum, int indexnum, int index, int ways, char* wbehavior, bool setisfull, int bs){
    int tindex = targetindex(cache, ways);
    for (int k = 0; k < bs; k++){
        cache[tindex].vals[k] = (int) mem[memblockindex + k];
    }
    cache[tindex].tag = tagnum;
    cache[tindex].lastins = insnum;
    cache[tindex].valid = 1;
    if (setisfull && (strcmp(wbehavior, "wb") == 0)){
        int wbindex = (cache[tindex].tag << (blocknum + indexnum)) + (index << (blocknum + indexnum));
        for (int k = 0; k < bs; k++){
            mem[wbindex + k] = cache[tindex].vals[k];
        }
    }
}


int main(int argc, char* argv[]){
    char* fname = argv[1];
    int size = atoi(argv[2]);
    int ways = atoi(argv[3]);           //extract args
    char* wbehavior = argv[4];
    int bs = atoi(argv[5]);

    int num_frames = (size * 1024) / bs;
    int sets = num_frames / ways;       //dimensions calc


    struct block** cache;            //creating cache and main memory with proper dimensions
    int mainmem[65536];
    for (int k = 0; k < 65536; k++){
        mainmem[k] = 0;
    }
    cache = (struct block**) calloc(sets, sizeof(struct block*));
    for (int k = 0; k < sets; k++){
        cache[k] = (struct block*) calloc(ways, sizeof(struct block));
    }

    int indexnum = log(sets) / log(2);
    int blocknum = log(bs) / log(2);

    FILE *f1 = fopen(fname, "r");
    if (f1 == NULL){
        printf("ERROR: COULD NOT OPEN FILE");   //open file
        return 1;
    }
    int r;
    int inscount = 0;
    char ins[8]; 
    int addr; 
    int bytes;
    char val[10];
    while (r = fscanf(f1, "%s %x %d", ins, &addr, &bytes) != EOF){
        int words[8];
        char horm[5] = "";
        if (strcmp(ins, "store") == 0){
            fscanf(f1, "%s", val);
        }

        int blockoffset = grabblockoffset(addr, blocknum);
        int index = grabindex(addr, indexnum, blocknum);
        int tag = grabtag(addr, indexnum, blocknum);
        int memblockindex = grabmemblockindex(addr, indexnum, blocknum);
        bool check = setisfull(cache[index], ways);
        if (strcmp("store", ins) == 0){
            bool hit = writecache(cache[index], blockoffset, tag, val, bytes, ways, inscount);
            if (strcmp(wbehavior, "wt") == 0){
                writemem(mainmem, addr, val, bytes);
            }

            if (hit){
                strcpy(horm, "hit");
            }
            else{
                strcpy(horm, "miss");
                writemem(mainmem, addr, val, bytes);
                evictandreplace(cache[index], mainmem, tag, inscount, memblockindex, blocknum, indexnum, index, ways, wbehavior, check, bs);
            }
        }
        // printf("%x%x", cache[index][0].vals[27], cache[index][0].vals[28]);
        if (strcmp("load", ins) == 0){
            bool read = readcache(cache[index], blockoffset, tag, size, ways, inscount, words);
            if (read){
                strcpy(horm, "hit");
            }
            else{
                strcpy(horm, "miss");
                readmem(mainmem, addr, size, words);
                evictandreplace(cache[index], mainmem, tag, inscount, memblockindex, blocknum, indexnum, index, ways, wbehavior, check, bs);
            }
        }
        printf("%s %04x %s ", ins, addr, horm);
        if (strcmp("load", ins) == 0){
            for (int k = 0; k < bytes; k++){
                printf("%02x", words[k]);
            }
        }
        printf("\n");
        inscount++;
    }
    return 0;
}



