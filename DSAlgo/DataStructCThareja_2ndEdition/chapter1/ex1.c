#include <stdio.h>

int main(int argc, char const *argv[]) {
        int i=0, inp[10];
        for ( i = 0; i < 10; i++)
                scanf("%d", &inp[i]);
        for ( i = 0; i < 10; i++) {
                printf("%d", inp[i]);
                if(i%3==2)
                        printf(",\n");
                else
                        printf(", ", );
        }

        return 0;
}
