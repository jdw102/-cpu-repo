#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct person {
    char *name;
    char *a[2];
    struct person* next;
};

bool search(struct person* head, char target[]){
    // printf("Checking if exists...\n");
    while (head != NULL){
        printf("Scanning: %s\n", head->name);
        if (strcmp(target, head->name) == 0){
            printf("found\n");
            return true;
        }
        head = head->next;
    }
    // printf("not found\n");
    return false;
}

void mutate(struct person* head, char target[], char victim[]){
    while(head != NULL){
        if(strcmp(target, head->name) == 0){
            if (head->a[0] = NULL){
                head->a[0] = victim;
            }
            else if(strcmp(head->a[0], victim) > 0){
                char* temp;
                temp = head->a[0];
                head->a[0] = victim;
                head->a[1] = temp;
            }
            else {
                head->a[1] = victim;
            }
        }
        head = head->next;
    }
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
            struct person* p = (struct person*) malloc(sizeof(struct person));
            if (c == ' '){
                // printf("Got infected\n");
                if (search(previous, currname) == true){
                    printf("Node exists\n");
                    continue;
                }
                else{
                    printf("Node does not exist\n");
                    char copyname[30];
                    strcpy(copyname, currname);
                    p->name = copyname;
                    p->next = previous;
                    printf("Current node (p): %s %s %s\n", p->name, p->a[0], p->a[1]);
                    previous = p;
                }
            }
            if (c == '\n'){
                // printf("Source\n");
                if (search(previous, currname) == true){
                    printf("Node exists\n");
                    mutate(previous, currname, previous->name);
                }
                else{
                    printf("Node does not exist\n");
                    char copyname[30];
                    char copylist[30];
                    strcpy(copyname, currname);
                    strcpy(copylist, previous->name);
                    p->name = copyname;
                    p->a[0] = copylist;
                    p->next = previous;
                    printf("Current node (p): %s %s %s\n", p->name, p->a[0], p->a[1]);
                    previous = p;
                }
            }
            // printf("%s %s %s\n", p->name, p->a[0], p->a[1]);
            iter++;
        }
        // printlist(final);
        return 0;
}



void sortlist(struct person* head){

}
