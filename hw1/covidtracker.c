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
    struct person* temp = (struct person*) malloc(sizeof(person));
    struct person* n = (struct person*) malloc(sizeof(person));
    n= NULL;
    temp = head;
    while (temp != NULL){
        if (strcmp(target, temp->name) == 0){
            return temp;
        }
        temp = temp->next;
    }
    return n;
}

void placenode(struct person* head, struct person* newnode){
    struct person* before = head;
    struct person* temp = head;
    bool last = true;
    while(temp != NULL){
        if (strcmp(temp->name, newnode->name) > 0){
            last = false;
            before->next = newnode;
            newnode->next = temp;
            break;
        }
        if (before != temp){
            before = before->next;
        }
        temp = temp->next;
    }
    if (last){
        before->next = newnode;
    }
    return;
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
        char oldname[30];
        previous = NULL;
        final = NULL;
        char c;
        int iter = 0;
        while (true){
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
            if (strcmp(currname, "DONE") == 0){
                final = previous;
                break;
            }

            if (c == ' '){
                struct person* p = (struct person*) malloc(sizeof(struct person));
                strcpy(p->name, currname);
                if (previous == NULL || strcmp(p->name, previous->name) < 0){
                    p->next = previous;
                    previous = p;
                    strcpy(oldname, p->name);
                }
                else{
                    placenode(previous, p);
                    strcpy(oldname, p->name);
                }
            }
            if (c == '\n'){
                struct person* grabbed = (struct person*) malloc(sizeof(struct person));
                grabbed = grab(previous, currname);
                if (grabbed == NULL){
                    struct person* p = (struct person*) malloc(sizeof(struct person));
                    strcpy(p->name, currname);
                    strcpy(p->p1, oldname);
                    p->p1count++;;
                    if (strcmp(p->name, previous->name) < 0){
                        p->next = previous;
                        previous = p;  
                        strcpy(oldname, p->name);
                    }
                    else{
                        placenode(previous, p);
                        strcpy(oldname, p->name);
                    }
                }
                else{
                    if (grabbed->p1count == 0){
                        strcpy(grabbed->p1, oldname);
                        grabbed->p1count++;
                        strcpy(oldname, grabbed->name);
                    }
                    else{
                        if (strcmp(grabbed->p1, oldname) > 0){
                            strcpy(grabbed->p2, grabbed->p1);
                            grabbed->p2count++;
                            strcpy(grabbed->p1, oldname);
                            grabbed->p1count++;
                            strcpy(oldname, grabbed->name);
                        }
                        else{
                            strcpy(grabbed->p2, oldname);
                            grabbed->p2count++;
                            strcpy(oldname, grabbed->name);
                        }
                    }
                }
            }
        }
        printlist(final);
        return 0;
}