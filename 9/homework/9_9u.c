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

int insert_after_even_columns(double **a, int n, int *m, double value){
    int i, j, t, add = *m / 2, newm = *m + add;
    double **rows;
    if (add == 0) return 1;
    rows = (double **)malloc(n * sizeof(double *));
    if (rows == NULL) return 0;
    for (i = 0; i < n; i++){
        rows[i] = (double *)malloc(newm * sizeof(double));
        if (rows[i] == NULL){
            free_matrix(rows, i);
            return 0;
        }
    }
    for (i = 0; i < n; i++){
        t = 0;
        for (j = 0; j < *m; j++){
            rows[i][t++] = a[i][j];
            if ((j + 1) % 2 == 0)      
                rows[i][t++] = value;
        }
        free(a[i]);
        a[i] = rows[i];
    }
    free(rows);                       
    *m = newm;
    return 1;
}

int main(){
    int n, m, mode;
    double **a, value;

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

    printf("Value for the new columns: ");
    scanf("%lf", &value);
    if (m < 2) printf("There are no even columns - nothing to insert\n");
    if (insert_after_even_columns(a, n, &m, value)){
        printf("Result (%d x %d):\n", n, m);
        print_matrix(a, n, m);
    } else {
        printf("Not enough memory - the matrix is unchanged\n");
    }
    free_matrix(a, n);
    return 0;
}
