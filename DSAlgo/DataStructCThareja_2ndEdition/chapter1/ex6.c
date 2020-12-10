#include <stdio.h>

int main(int argc, char const *argv[]) {
        float num;
        scanf("%f", &num);
        int int_num = (int)num;
        printf("%d\n", (int_num%10));
        return 0;
}
