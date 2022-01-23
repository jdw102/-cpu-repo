#include<stdio.h>
#include<stdlib.h>

float* points_ptr;

    float foo(float* x_ptr, float *y_ptr, float z){
        if (*x_ptr > *y_ptr + z){
            return *x_ptr;
            } 
        else {
            return *y_ptr+z;
            }
    }

    int main() {
        float avg_per_game = 21.34;
        points_ptr = &avg_per_game;
        float* rebounds_ptr = (float*) malloc(2*sizeof(float));
        rebounds_ptr[0] = 7.0;
        *(rebounds_ptr+1) = 4.0;
        float num = foo(points_ptr, rebounds_ptr, rebounds_ptr[1]);
        free(rebounds_ptr);
        if (num > 10.5){
            printf("0\n");
            return 0;
        }       
        else {
            printf("1\n");
            return 1;
        }   
    }
    