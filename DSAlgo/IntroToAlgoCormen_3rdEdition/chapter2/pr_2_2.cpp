#include <iostream>

using namespace std;

void bubbleSort(int *a, int n) {
	for (int i = 0; i < n; ++i)
	{
		for (int j = n - 2; j >= i; j--) {
			if (a[j] < a[j + 1])
			{
				int t = a[j];
				a[j] = a[j + 1];
				a[j + 1] = t;
			}
		}
	}
}


int main(int argc, char const *argv[])
{
	int a[10] = {5, 9, 6, 3, 7, 1, 6, 0, 8, 10};
	bubbleSort(a, 10);
	for (int i = 0; i < 10; ++i)
		cout << a[i] << " ";
	cout << endl;
	return 0;
}