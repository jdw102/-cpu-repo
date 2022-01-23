#include<stdio.h>
#include<stdlib.h>

typedef struct HoopsPlayer {
    int num;
    float ppg;
    struct HoopsPlayer* next;
} HoopsPlayer_t;

HoopsPlayer_t sortlist(int numplayers, HoopsPlayer_t *p){
    HoopsPlayer_t players[numplayers];
    HoopsPlayer_t *previous = NULL;
    HoopsPlayer_t *final = NULL;
    int l = 0;
    while(p != NULL){
        players[l] = *p;
        l++;
        p = p->next;
    }
    for (int i = 0; i < numplayers; i++){
        for (int j = i + 1; j < numplayers; j++){
            if (players[j].ppg < players[i].ppg){
                HoopsPlayer a = players[i];
                players[i] = players[j];
                players[j] = a;
            }
        }
    }
    for (int k = 0; k < numplayers; k++){
        printf("%d, %f \n", players[k].num, players[k].ppg);
    } 
}

int main(int argc, char *argv[]){
    int numplayers = 0;
    HoopsPlayer_t *previous = NULL;
    HoopsPlayer_t *final = NULL;
    while (true){
        int num;
        float ppg;

        printf("Number: ");
        scanf("%d", &num);
        if (num == -1){
            final = previous;
            break;
        }
        HoopsPlayer_t *current = (HoopsPlayer_t*) malloc(sizeof(HoopsPlayer_t));
        printf("PPG: ");
        scanf("%f", &ppg);

        current->num = num;
        current->ppg = ppg;
        current->next = previous;
        previous = current;
        numplayers++;
    }
    sortlist(numplayers, final);
}