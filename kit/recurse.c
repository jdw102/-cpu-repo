#include<stdio.h>
#include<stdlib.h>

int function(int n){
    if (n == 0){
        return -2;
    }
    return (3 * n) + ( 2 * (function(n - 1))) - 2;
}


int main(int argc, char* argv[]){
    int n = atoi(argv[1]);
    int fn = function(n);
    printf("%d\n", fn);
    return 0;
}

