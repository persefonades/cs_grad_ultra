#include <stdio.h>

int main(int argc, char const *argv[]) {
        float a, b;
        int c;
        scanf("%f%f", &a, &b);
        c = (int)(a+b);
        printf("A = %lf\nB = %lf\nC = %d\n", a, b, c );
        return 0;
}
