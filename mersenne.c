#include<stdio.h>

int main(int argc, char* argv[]){
    int n = (int) *argv[1];
    int ret = 1;
    for (int i = 0; i < n; i++){
        ret = ret * 2;
    }
    printf(ret - 1);
    return ret - 1;
}
