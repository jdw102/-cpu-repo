#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct person {
    char name[30];
    char p1[30];
    char p2[30];
    int p1count = 0;
    int p2count = 0;
    struct person* next;
};

struct person* grab(struct person* head, char target[]){
    // printf("Checking if exists...\n");
    struct person* temp = (struct person*) malloc(sizeof(person));
    struct person* n = (struct person*) malloc(sizeof(person));
    n= NULL;
    temp = head;
    while (temp != NULL){
        // printf("Scanning: %s\n", temp->name);
        if (strcmp(target, temp->name) == 0){
            // printf("found\n");
            return temp;
        }
        temp = temp->next;
    }
    // printf("not found\n");
    return n;
}
void sortlist(struct person* head){
        struct person* temp = head;
        struct person* after = head->next;
        struct person* previous = head;
        int iter = 0;
        while (after != NULL){
            if (strcmp(temp->name, next->name) < 0){
                temp->next = after->next;
                after->next = temp;
                if (iter > 0){
                    previous-> next = after;
                }
                after = temp->next;
                if (iter > 0){
                    previous- = previous->next;
                }
                if (iter == 0){
                    head = previous;
                }
            }
            else{
                after = after->next;
                temp = temp->next;
                if (iter > 0){
                    previous = previous->next;
                }
            }
            iter++;
            if (checkalph){
                return sortlist(head);
            }
            return void;
        }

    }
bool checkalph(struct person* head){
    struct person* temp = head;
    while(temp != NULL){
        if (strcmp(temp->name, temp->next->name) > 0){
            return false;
        }
        temp = temp->next;
    }
    return true;
}

void printlist(struct person* head){
    while (head != NULL){
        printf("%s %s %s\n", head->name, head->p1, head->p2);
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
        struct person* final = (struct person*) malloc(sizeof(struct person));
        struct person* previous = (struct person*) malloc(sizeof(struct person));
        previous = NULL;
        final = NULL;
        char c;
        int iter = 0;
        while (true){
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
            // printf("Currname: %s\n", currname);
            if (strcmp(currname, "DONE") == 0){
                final = previous;
                break;
            }

            if (c == ' '){
                // printf("new victim\n");
                struct person* p = (struct person*) malloc(sizeof(struct person));
                strcpy(p->name, currname);
                p->next = previous;
                previous = p;
                }
            if (c == '\n'){
                struct person* grabbed = (struct person*) malloc(sizeof(struct person));
                grabbed = grab(previous, currname);
                if (grabbed == NULL){
                    // printf("new infector\n");
                    struct person* p = (struct person*) malloc(sizeof(struct person));
                    strcpy(p->name, currname);
                    strcpy(p->p1, previous->name);
                    p->p1count++;;
                    // printf(", %s infected %s", p->name, p->p1);
                    p->next = previous;
                    previous = p;
                }
                else{
                    // printf("update\n");
                    if (grabbed->p1count == 0){
                        // printf("%s", grabbed->p1);
                        // printf("test\n");
                        strcpy(grabbed->p1, previous->name);
                        grabbed->p1count++;
                        // printf(", %s infected %s", grabbed->name, grabbed->p1);
                    }
                    else{
                        if (strcmp(grabbed->p1, previous->name) > 0){
                            strcpy(grabbed->p2, grabbed->p1);
                            grabbed->p2count++;
                            strcpy(grabbed->p1, previous->name);
                            grabbed->p1count++;
                        }
                        else{
                            strcpy(grabbed->p2, previous->name);
                            grabbed->p2count++;
                        // printf(", %s infected %s and %s", grabbed->name, grabbed->p1, grabbed->p2);
                        }
                    }
                }
            }
        }
        printlist(final);
        return 0;
}