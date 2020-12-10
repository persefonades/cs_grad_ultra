#include <stdio.h>

int main(int argc, char const *argv[]) {
        int num;
        scanf("%d", &num);
        if (num%2)
                printf("Not divisible by 2\n");
        else
                printf("Divisible by 2\n");
        return 0;
}
