#include <stdio.h>

int main(){
    double x, xk = 1;
    int n, k;
    printf("Enter x and the number of the last element n: ");
    scanf("%lf %d", &x, &n);
    if (n < 0){
        printf("n must be >= 0\n");
        return 0;
    }
    printf("x_0 = %.10g\n", xk);
    for (k = 1; k <= n; k++){
        xk = xk * (-x * x) / ((2.0 * k - 1) * (2.0 * k));
        printf("x_%d = %.10g\n", k, xk);
    }
    return 0;
}
