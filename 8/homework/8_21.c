#include <stdio.h>
#define MAXN 100

void min_to_first_row(double a[][MAXN], int n, int m){
    int i, j, imin;
    double t;
    for (j = 0; j < m; j++){
        imin = 0;
        for (i = 1; i < n; i++)
            if (a[i][j] < a[imin][j]) imin = i;
        if (imin != 0){
            t = a[0][j];
            a[0][j] = a[imin][j];
            a[imin][j] = t;
        }
    }
}

void print_matrix(double a[][MAXN], int n, int m){
    int i, j;
    for (i = 0; i < n; i++){
        for (j = 0; j < m; j++) printf("%8.2f", a[i][j]);
        printf("\n");
    }
}

int main(){
    static double a[MAXN][MAXN];
    int n, m, i, j;
    printf("Enter n and m (< %d): ", MAXN);
    scanf("%d %d", &n, &m);
    if (n < 1 || m < 1 || n >= MAXN || m >= MAXN){
        printf("Wrong size\n");
        return 0;
    }
    for (i = 0; i < n; i++){
        printf("Row %d: ", i);
        for (j = 0; j < m; j++) scanf("%lf", &a[i][j]);
    }
    min_to_first_row(a, n, m);
    printf("Result:\n");
    print_matrix(a, n, m);
    return 0;
}
