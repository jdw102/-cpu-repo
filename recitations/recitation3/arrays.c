#include<stdio.h>
#include<stdlib.h>

int sumArray(int* ptr){
    int count = 0;
    for (int k = 0; k < 100; k++){
        count += ptr[k];
    }
    return count;
}

int main(int argc, char* argv[]){
    int a[100];
    for (int k = 0; k < 100; k++){
        a[k] = k;
    }
    printf("%d\n", sumArray(a));
}