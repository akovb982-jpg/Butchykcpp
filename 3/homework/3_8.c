#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

int main(){
    uint32_t a, b;
    int32_t x, y;
    int64_t p;
    printf("Enter two natural 32-bit numbers: ");
    if (scanf("%" SCNu32 " %" SCNu32, &a, &b) != 2){
        printf("Input error\n");
        return 0;
    }
    if (a > UINT32_MAX - b)
        printf("Overflow: the sum does not fit into 32 bits\n");
    else
        printf("a + b = %" PRIu32 "\n", (uint32_t)(a + b));

    printf("Enter two signed 32-bit integers: ");
    if (scanf("%" SCNd32 " %" SCNd32, &x, &y) != 2){
        printf("Input error\n");
        return 0;
    }
    p = (int64_t)x * y;   
    if (p > INT32_MAX || p < INT32_MIN)
        printf("Overflow: the product does not fit into 32 bits\n");
    else
        printf("x * y = %" PRId32 "\n", (int32_t)p);
    return 0;
}
