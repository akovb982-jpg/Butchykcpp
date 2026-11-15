#include <stdio.h>
#define MAXN 1000

double min_odd_positions(const double a[], int n){
    double m = a[0];
    int i;
    for (i = 2; i < n; i += 2)
        if (a[i] < m) m = a[i];
    return m;
}

int main(){
    double a[MAXN];
    int n, i;
    printf("n = ");
    scanf("%d", &n);
    if (n < 1 || n > MAXN){
        printf("Wrong n\n");
        return 0;
    }
    for (i = 0; i < n; i++){
        printf("a%d = ", i + 1);
        scanf("%lf", &a[i]);
    }
    printf("min(a1, a3, ...) = %g\n", min_odd_positions(a, n));
    return 0;
}
