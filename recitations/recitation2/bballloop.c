#include<stdio.h>
#include<stdlib.h>

typedef struct HoopsPlayer {
    int num;
    float ppg;
} HoopsPlayer_t;

void sortList(HoopsPlayer list[], int numplayers){
    printf("Sorted\n");
    for (int i = 0; i < numplayers; i++){
        for (int j = i + 1; j < numplayers; j++){
            if (list[j].ppg < list[i].ppg){
                HoopsPlayer a = list[i];
                list[i] = list[j];
                list[j] = a;
            }
        }
    }
}

int main (){
    HoopsPlayer_t list[10];
    int numplayers;
    for (numplayers = 0; numplayers < 10; numplayers++){
        int num;
        float ppg;

        printf("Number: ");
        scanf("%d", &num);
        if (num == -1){
            break;
        }
        printf("PPG: ");
        scanf("%f", &ppg);
        list[numplayers].num = num;
        list[numplayers].ppg = ppg;
    }
    for (int i = 0; i < numplayers; i++){
        printf("%d, %f \n", list[i].num, list[i].ppg);
    }
    sortList(list, numplayers);
    for (int i = 0; i < numplayers; i++){
        printf("%d, %f \n", list[i].num, list[i].ppg);
    }
    return 0;
}