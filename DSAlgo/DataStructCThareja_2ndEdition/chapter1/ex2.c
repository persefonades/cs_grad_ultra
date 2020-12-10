#include <stdio.h>

int main(int argc, char const *argv[]) {
        int i, sum=0, count=0;
        for(i=1; i<=200; i++) {
                if(i%2==0) {
                        sum+=i;
                        count++;
                }
        }
        printf("Count = %d\n", count);
        printf("Sum = %d\n", sum);
        return 0;
}
