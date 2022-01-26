#include<stdio.h>
#include<stdlib.h>
#include<string.h>


struct person {
    char name[30];
    char p1[30];
    char p2[30];
    int p1count;
    int p2count;
    struct person* next;
};

struct person* grab(struct person* head, char target[]){
    struct person* temp = head;
    temp = head;
    while (temp != NULL){
        if (strcmp(target, temp->name) == 0){
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
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
    int iter = 0;
    while (head != NULL){
        if (iter !=0){
            printf("%s %s %s\n", head->name, head->p1, head->p2);
        }
        struct person* temp = head;
        head = head->next;
        free(temp);
        iter++;
    }
}


int main(int argc, char* argv[]){
        char* filename = argv[1];
        FILE *f1 = fopen(filename, "r");
        if (f1 == NULL){
            printf("ERROR: COULD NOT OPEN FILE");
            return 1;
        }
        struct person* previous = (struct person*) malloc(sizeof(struct person));
        strcpy(previous->name, "");
        strcpy(previous->p1, "");
        previous->p1count = 0;
        strcpy(previous->p2, "");
        previous->p2count = 0;
        previous->next = NULL;
        char oldname[30];
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
                break;
            }

            if (c == ' '){
                struct person* p = (struct person*) malloc(sizeof(struct person));
                strcpy(p->p1, "");
                p->p1count = 0;
                strcpy(p->p2, "");
                p->p2count = 0;
                strcpy(p->name, currname);
                p->next = NULL;
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
                struct person* grabbed = grab(previous, currname);
                if (grabbed == NULL){
                    struct person* p = (struct person*) malloc(sizeof(struct person));
                    strcpy(p->p1, "");
                    p->p1count = 0;
                    strcpy(p->p2, "");
                    p->p2count = 0;
                    strcpy(p->name, currname);
                    strcpy(p->p1, oldname);
                    p->next = NULL;
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
        printlist(previous);
        return 0;
}