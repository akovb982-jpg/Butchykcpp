#include <stdio.h>

int main(){
    unsigned n, k;
    double a_prev2 = 2, a_prev = 1; 
    double b_prev = 0;             
    double ak, bk, pw = 27, s;        

    printf("n = ");
    scanf("%u", &n);
    if (n < 1){
        printf("n must be natural\n");
        return 0;
    }
    s = 27.0 / (2 * 1 + 1);            
    pw = 243;                        
    if (n >= 2) s += pw / (1 * 0 + 1);    
    for (k = 3; k <= n; k++){
        bk = 2 * b_prev + a_prev;
        ak = a_prev / (k + 1) + a_prev2 + bk;
        pw *= 9;                       
        s += pw / (ak * bk + 1);
        a_prev2 = a_prev;
        a_prev = ak;
        b_prev = bk;
    }
    printf("S = %.10g\n", s);
    return 0;
}
