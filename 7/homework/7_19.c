#include <stdio.h>
#define MAXC 100

int poly_from_roots(const double roots[], int m, double c[]){
    int i, k;
    c[0] = 1;
    for (i = 0; i < m; i++){
        c[i + 1] = c[i];      
        for (k = i; k >= 1; k--)
            c[k] = c[k - 1] - roots[i] * c[k];
        c[0] = -roots[i] * c[0];
    }
    return m;
}

void print_poly(const double c[], int deg){
    int k, first = 1;
    for (k = deg; k >= 0; k--){
        if (c[k] == 0) continue;
        if (!first) printf(c[k] > 0 ? " + " : " - ");
        else if (c[k] < 0) printf("-");
        {
            double v = c[k] < 0 ? -c[k] : c[k];
            if (v != 1 || k == 0) printf("%g", v);
        }
        if (k >= 2) printf("x^%d", k);
        else if (k == 1) printf("x");
        first = 0;
    }
    if (first) printf("0");
    printf("\n");
}

int main(){
    double roots[MAXC - 1], c[MAXC];
    int m, i, deg;

    printf("Number of roots (1..%d): ", MAXC - 1);
    scanf("%d", &m);
    if (m < 1 || m > MAXC - 1){
        printf("Wrong number of roots\n");
        return 0;
    }
    for (i = 0; i < m; i++){
        printf("x[%d] = ", i);
        scanf("%lf", &roots[i]);
    }
    deg = poly_from_roots(roots, m, c);

    printf("Coefficients (from x^%d down to x^0):\n", deg);
    for (i = deg; i >= 0; i--) printf("%g ", c[i]);
    printf("\nP(x) = ");
    print_poly(c, deg);
    return 0;
}
