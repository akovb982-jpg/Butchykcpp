#include <stdio.h>
#include <math.h>

int main(){
    double x;
    printf("x = ");
    scanf("%lf", &x);
    printf("cos(%g) = %f\n", x, cos(x));
    return 0;
}
