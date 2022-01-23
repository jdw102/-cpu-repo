#include<stdio.h>
 
 int main(int argc, char *argv[]){
    int arr[3];
    int* ptr;
    for (int k = 0; k < 3; k++){
        arr[k] = 1;
    }
    *ptr = 5;
    return 0;
 }