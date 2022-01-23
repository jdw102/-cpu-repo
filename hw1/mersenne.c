#include<stdio.h>
#include<stdlib.h>

int main(int argc, char* argv[]){
    int n = atoi(argv[1]);
    int ret = 1;
    for (int i = 0; i < n; i++){
        ret = (ret * 2);
    }
    printf("%d\n", ret - 1);
    return 0;
