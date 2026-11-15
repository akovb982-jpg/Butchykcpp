#include <stdio.h>
#include <math.h>

int main(){
    double eps, s = 0, pi;
    long long n = 0;

    printf("eps = ");
    scanf("%lf", &eps);
    if (eps <= 0){
        printf("eps must be positive\n");
        return 0;
    }
    do {
        double k4;
        n++;
        k4 = (double)n * n * n * n;
        s += 1 / k4;
    } while (1.0 / (3.0 * n * n * n) >= eps);

    pi = sqrt(sqrt(90 * s));
    printf("pi ~ %.15f (terms: %lld)\n", pi, n);
    printf("acos(-1) = %.15f, error = %e\n", acos(-1.0), fabs(pi - acos(-1.0)));
    return 0;
}
