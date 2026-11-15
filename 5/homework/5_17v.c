#include <stdio.h>
#include <math.h>

int main(){
    double x, eps, a = 1, s = 0;
    int k = 0;

    printf("Enter x and eps: ");
    scanf("%lf %lf", &x, &eps);
    if (x == 0 || eps <= 0){
        printf("Wrong input (x != 0, eps > 0)\n");
        return 0;
    }
    while (fabs(a) >= eps){
        s += a;
        k++;
        a = a * x * x / (2.0 * k);
    }
    printf("Sum = %.12f\n", s);
    printf("Terms used: %d\n", k);
    printf("Check: exp(x^2/2) = %.12f\n", exp(x * x / 2));
    return 0;
}
