#include <stdio.h>

int create_file(const char *fname){
    FILE *f = fopen(fname, "wb");
    int n, i, x;
    if (f == NULL) return 0;
    printf("How many numbers to write into %s? ", fname);
    if (scanf("%d", &n) != 1 || n < 0){ fclose(f); return 0; }
    for (i = 0; i < n; i++){
        printf("x%d = ", i + 1);
        scanf("%d", &x);
        fwrite(&x, sizeof(int), 1, f);
    }
    fclose(f);
    return 1;
}

void print_file(const char *fname){
    FILE *f = fopen(fname, "rb");
    int x;
    printf("%s: ", fname);
    if (f == NULL){ printf("cannot open\n"); return; }
    while (fread(&x, sizeof(int), 1, f) == 1) printf("%d ", x);
    printf("\n");
    fclose(f);
}
int check_balance(const char *fname){
    FILE *f = fopen(fname, "rb");
    int x, pos = 0, neg = 0, zero = 0;
    if (f == NULL) return -1;
    while (fread(&x, sizeof(int), 1, f) == 1){
        if (x > 0) pos++;
        else if (x < 0) neg++;
        else zero++;
    }
    fclose(f);
    return pos == neg && zero == 0;
}

int rewrite(const char *fname, const char *hname, const char *gname){
    FILE *f, *g, *h;
    int x;
    f = fopen(fname, "rb");
    if (f == NULL) return 0;
    g = fopen(gname, "wb");
    h = fopen(hname, "wb");
    if (g == NULL || h == NULL){
        fclose(f);
        if (g) fclose(g);
        if (h) fclose(h);
        return 0;
    }
    while (fread(&x, sizeof(int), 1, f) == 1){
        if (x > 0) fwrite(&x, sizeof(int), 1, g);
        else fwrite(&x, sizeof(int), 1, h);
    }
    fclose(f);
    fclose(h);
    h = fopen(hname, "rb");
    if (h == NULL){ fclose(g); return 0; }
    while (fread(&x, sizeof(int), 1, h) == 1)
        fwrite(&x, sizeof(int), 1, g);
    fclose(h);
    fclose(g);
    return 1;
}

int main(){
    int ok;
    if (!create_file("F.bin")){
        printf("Cannot create F.bin\n");
        return 1;
    }
    print_file("F.bin");
    ok = check_balance("F.bin");
    if (ok < 0){
        printf("Cannot open F.bin\n");
        return 1;
    }
    if (ok == 0){
        printf("The file does not contain an equal number of positive and negative "
               "numbers (or contains zeros). Nothing is done.\n");
        return 0;
    }
    if (!rewrite("F.bin", "H.bin", "G.bin")){
        printf("File error\n");
        return 1;
    }
    print_file("G.bin");
    return 0;
}
