#include <stdio.h>
#include <stdint.h>

int main(void) {
    printf("char    %zu\n", sizeof(char));
    printf("short   %zu\n", sizeof(short));
    printf("int     %zu\n", sizeof(int));
    printf("long    %zu\n", sizeof(long));
    printf("float   %zu\n", sizeof(float));
    printf("double  %zu\n", sizeof(double));
    printf("void *  %zu\n", sizeof(void *));
    printf("int32_t %zu\n", sizeof(int32_t));
    return 0;
}
