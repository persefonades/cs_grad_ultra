#include <stdio.h>

int main(int argc, char const *argv[]) {
        float basic, hra, ta, gross;
        scanf("%f\n", &basic);
        hra = 0.1 * basic;
        ta = 0.05 * basic;
        gross = basic + hra + ta;
        printf("%0.2f\n", gross);
        return 0;
}
