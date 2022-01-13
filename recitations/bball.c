#include<stdio.h>
int main (){
    char str[80];
    int height;
    int points;

    printf("Who is your favorite Duke Basketball player?: ");
    scanf("%s", str);
    printf("What is their height in inches?: ");
    scanf("%d", &height);
    printf("What is their average points per game?: ");
    scanf("%d", &points);
    float final =  points / (float) height;
    printf("%s scored %f per inch\n", str, final);
    return 0;
}