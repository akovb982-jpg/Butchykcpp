#include <stdio.h>

int main(){
    char a;
    printf("Enter a digit: ");
    scanf(" %c", &a);
    printf("- %c - %c - %c\n", a, a, a);
    printf("%c | %c | %c\n", a, a, a);
    printf("- %c - %c - %c\n", a, a, a);
    return 0;
}
