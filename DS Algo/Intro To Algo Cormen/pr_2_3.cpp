#include <iostream>

using namespace std;

int naivePolyEval(int *a, int n, int x) {
	int y = 0;
	for (int i = 0; i <= n; ++i)
	{
		int yi = 1;
		for (int j = 1; j <= i; ++j)
		{
			yi = yi * x;
		}
		y += a[i] * yi;
	}
	return y;
}

int hornerPolyEval(int *a, int n, int x) {
	int y = 0;
	for (int i = n; i >= 0; --i)
	{
		y = a[i] + x * y;
	}
	return y;
}

int main(int argc, char const *argv[])
{
	int a[] = {5, 9, 6};
	int x = 3;
	cout << naivePolyEval(a, 2, 4) << endl;
	cout << hornerPolyEval(a, 2, 4) << endl;
	return 0;
}