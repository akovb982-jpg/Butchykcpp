#include <stdio.h>

double poly(double x){
    double t = x + 1;      
    double t2 = t * t;     
    double t4 = t2 * t2;   
    return t4 * t;         
}

int main(){
    double x;
    printf("x = ");
    scanf("%lf", &x);
    printf("y = %f\n", poly(x));
    return 0;
}
