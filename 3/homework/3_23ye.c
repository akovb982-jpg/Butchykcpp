#include <stdio.h>
#include <math.h>
#include <float.h>

double softExponential(double a, double x){
    if (a < 0){
        double arg = 1 - a * (x + a);
        if (arg <= 0) return -DBL_MAX;
        return -log(arg) / a;
    }
    if (a == 0) return x;
    {
        double e = exp(a * x);
        if (e > DBL_MAX) return DBL_MAX;   
        return (e - 1) / a + a;
    }
}

double softExponential_derivative(double a, double x){
    if (a < 0){
        double arg = 1 - a * (x + a);
        if (arg <= 0) return DBL_MAX;
        return 1 / arg;
    }
    if (a == 0) return 1;
    {
        double e = exp(a * x);
        return (e > DBL_MAX) ? DBL_MAX : e;
    }
}

int main(){
    double a, x;
    printf("Enter a and x: ");
    scanf("%lf %lf", &a, &x);
    printf("softExponential(%g, %g)  = %g\n", a, x, softExponential(a, x));
    printf("softExponential'(%g, %g) = %g\n", a, x, softExponential_derivative(a, x));
    return 0;
}
