#include <iostream>

using namespace std;


int main(int argc, char const *argv[])
{
    int a[5] = {0,1,0,1,1}, b[5] = {1,0,1,0,1}, c[6];
    int carry = 0;
    for (int i = 4; i>=0; i--)
    {
        c[i+1] = (a[i]+b[i]+carry)%2;
        carry = (a[i]+b[i]+carry)/2;
    }
    c[0]=carry;
    for (int i = 0; i<6; i++)
    {
    	cout<<c[i]<<" ";
    }

    return 0;
}