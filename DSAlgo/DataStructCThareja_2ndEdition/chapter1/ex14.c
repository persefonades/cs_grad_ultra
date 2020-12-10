#include <stdio.h>
#include <math.h>

double areaHeron(double a, double b, double c){
        double s, area;
        s = (a + b + c) / 2;
        area = sqrt(s * (s-a) * (s-b) * (s-c));
        return area;
}

int main(int argc, char const * argv[])
{
        double a, b, c;
        scanf("%lf %lf %lf", &a, &b, &c);
        printf("%.6f", areaHeron(a,b,c));
        return 0;
}
