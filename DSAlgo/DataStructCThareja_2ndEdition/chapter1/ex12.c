#include <stdio.h>

int main(int argc, char const *argv[]) {
        double num;
        scanf("%lf", &num);
        printf("%.2f %.4f %.8f\n", num, num, num);
        return 0;
}
