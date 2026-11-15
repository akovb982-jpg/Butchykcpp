#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void free_matrix(double **a, int n){
    int i;
    if (a == NULL) return;
    for (i = 0; i < n; i++) free(a[i]);
    free(a);
}

double **create_matrix(int n, int m){
    int i;
    double **a = (double **)malloc(n * sizeof(double *));
    if (a == NULL) return NULL;
    for (i = 0; i < n; i++){
        a[i] = (double *)malloc(m * sizeof(double));
        if (a[i] == NULL){
            free_matrix(a, i);
            return NULL;
        }
    }
    return a;
}

void fill_matrix(double **a, int n, int m, int random){
    int i, j;
    for (i = 0; i < n; i++){
        if (!random) printf("Row %d: ", i + 1);
        for (j = 0; j < m; j++){
            if (random) a[i][j] = rand() % 2001 / 100.0 - 10;
            else scanf("%lf", &a[i][j]);
        }
    }
}

void print_matrix(double **a, int n, int m){
    int i, j;
    for (i = 0; i < n; i++){
        for (j = 0; j < m; j++) printf("%8.2f", a[i][j]);
        printf("\n");
    }
}

int insert_column_after(double **a, int n, int *m, int k, const double *col){
    int i, j;
    double *p;
    if (k < 0 || k > *m) return 0;
    for (i = 0; i < n; i++){
        p = (double *)realloc(a[i], (*m + 1) * sizeof(double));
        if (p == NULL){
            return 0;
        }
        a[i] = p;
    }
    for (i = 0; i < n; i++){
        for (j = *m; j > k; j--)
            a[i][j] = a[i][j - 1];
        a[i][k] = col[i];
    }
    (*m)++;
    return 1;
}

int main(){
    int n, m, k, i, mode;
    double **a, *col;

    srand((unsigned)time(NULL));
    printf("Enter N and M: ");
    if (scanf("%d %d", &n, &m) != 2 || n < 1 || m < 1){
        printf("Wrong size\n");
        return 1;
    }
    a = create_matrix(n, m);
    if (a == NULL){
        printf("Not enough memory\n");
        return 1;
    }
    printf("Fill: 1 - random, 0 - from console: ");
    scanf("%d", &mode);
    fill_matrix(a, n, m, mode == 1);
    printf("Matrix:\n");
    print_matrix(a, n, m);

    printf("Insert a column after column number k (0..%d, 0 = at the beginning): ", m);
    if (scanf("%d", &k) != 1 || k < 0 || k > m){
        printf("Wrong column number\n");
        free_matrix(a, n);
        return 1;
    }
    col = (double *)malloc(n * sizeof(double));
    if (col == NULL){
        printf("Not enough memory\n");
        free_matrix(a, n);
        return 1;
    }
    printf("Enter %d elements of the new column: ", n);
    for (i = 0; i < n; i++) scanf("%lf", &col[i]);

    if (insert_column_after(a, n, &m, k, col)){
        printf("Result (%d x %d):\n", n, m);
        print_matrix(a, n, m);
    } else {
        printf("Not enough memory - the matrix is unchanged\n");
    }
    free(col);
    free_matrix(a, n);
    return 0;
}
