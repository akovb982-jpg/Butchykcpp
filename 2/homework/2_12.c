#include <stdio.h>
#include <math.h>

double cone_volume(double r, double h){
    const double PI = acos(-1.0);
    return PI * r * r * h / 3;
}

int main(){
    double r, h;
    printf("Enter base radius r and height h: ");
    scanf("%lf %lf", &r, &h);
    if (r < 0 || h < 0){
        printf("Radius and height must be non-negative\n");
        return 0;
    }
    printf("V = %f\n", cone_volume(r, h));
    return 0;
}
