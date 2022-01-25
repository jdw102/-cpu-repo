#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct person {
    char *name;
    char *a[2];
    struct person* next;
};

struct person* grab(struct person* head, char target[]){
    // printf("Checking if exists...\n");
    while (head != NULL){
        printf("Scanning: %s\n", head->name);
        if (strcmp(target, head->name) == 0){
            printf("found\n");
            return head;
        }
        head = head->next;
    }
    // printf("not found\n");
    return NULL;
}


void printlist(struct person* head){
    while (head != NULL){
        printf("%s %s %s\n", head->name, head->a[0], head->a[1]);
        head = head->next;
    }
}


int main(int argc, char* argv[]){
        char* filename = argv[1];
        FILE *f1 = fopen(filename, "r");
        if (f1 == NULL){
            printf("ERROR: COULD NOT OPEN FILE");
            return 1;
        }
        int size = 0;
        struct person* final = (struct person*) malloc(sizeof(struct person));
        struct person* previous = (struct person*) malloc(sizeof(struct person));
        previous = NULL;
        final = NULL;
        char c;
        int iter = 0;
        while (true){
            printf("Next person\n");
            // if (iter == 1){
            //     printf("Previous node: %s %s %s\n", previous->name, previous->a[1], previous->a[2]);
            // }
            char currname[30] = "";
            int i = 0;
            for (c=getc(f1); c != EOF; c = getc(f1)){
                if (c == ' ' || c == '\n'){
                    i = 0;
                    break;
                }
                currname[i] = c;
                i++;
            }
            printf("Currname: %s\n", currname);
            if (strcmp(currname, "DONE") == 0){
                final = previous;
                break;
            }
            struct person* grabbed = (struct person*) malloc(sizeof(struct person));
            grabbed = grab(previous, currname);
            
            if (c == ' '){
                if (grabbed == NULL){
                    struct person* p = (struct person*) malloc(sizeof(struct person));
                    char copyname[30];
                    strcpy(copyname, currname);
                    p->name = copyname;
                    p->next = previous;
                    previous = p;
                }
                else{
                    continue;
                }
            }
            if (c == '\n'){
                if (grabbed = NULL){
                    struct person* p = (struct person*) malloc(sizeof(struct person));
                    char copyname[30];
                    char copylist[30];
                    strcpy(copyname, currname);
                    strcpy(copylist, previous->name);
                    p->name = copyname;
                    p->a[0] = copylist;
                    p->next = previous;
                    previous = p;
                }
                else{
                    char copyvic[30];
                    strcpy(copyvic, previous->name);
                    if (grabbed->a[0] == NULL){
                        grabbed->a[0] = copyvic;
                    }
                    else{
                        grabbed->a[1] = copyvic;
                    }
                }
            }
            // printf("%s %s %s\n", p->name, p->a[0], p->a[1]);
        }
        printlist(final);
        return 0;
}



void sortlist(struct person* head){

}
