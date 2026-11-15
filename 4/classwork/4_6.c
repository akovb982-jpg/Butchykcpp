/*
 * Розділ 4, задача 6 (аудиторна).
 * Скласти програму обчислення
 * а) sqrt(2 + sqrt(2 + ... + sqrt(2)))  (n коренів),
 * б) sqrt(3 + sqrt(6 + ... + sqrt(3(n-1) + sqrt(3n)))).
 */
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>

int main(){
    unsigned n, k;
    double a = 0, b;

    printf("n = ");
    scanf("%u", &n);
    if (n < 1){
        printf("n must be natural\n");
        return 0;
    }

    /* а) обчислюємо зсередини назовні */
    for (k = 1; k <= n; k++)
        a = sqrt(2 + a);
    printf("a) %.10f\n", a);

    /* б) найглибший корінь - sqrt(3n), далі sqrt(3k + попереднє) */
    b = sqrt(3.0 * n);
    for (k = n - 1; k >= 1; k--)
        b = sqrt(3.0 * k + b);
    printf("b) %.10f\n", b);
    return 0;
}
