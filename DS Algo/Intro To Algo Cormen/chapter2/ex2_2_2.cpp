#include <iostream>

using namespace std;


int main(int argc, char const *argv[])
{
	int a[10] = {5, 9, 6, 3, 7, 1, 6, 0, 8, 10};
	for (int i = 0; i < 10 - 1; ++i)
	{
		int min = i;
		for (int j = i + 1; j < 10; ++j)
			if (a[j] < a[min])
				min = j;
		int tem = a[min];
		a[min] = a[i];
		a[i] = tem;
	}

	for (int i = 0; i < 10; ++i)
		cout << a[i] << ", ";
	cout << endl;

	return 0;
}