#include <stdio.h>
#include <math.h>

int main(int argc, char const *argv[]) {
        float pr, rate, time, si, ci;
        scanf("%f %f %f", &pr, &rate, &time);
        si = pr * rate * time / 100;
        ci = pr * (pow((1 + rate/100), time)-1);
        printf("%.2f\n", si);
        printf("%.2f\n", ci);
        return 0;
}
