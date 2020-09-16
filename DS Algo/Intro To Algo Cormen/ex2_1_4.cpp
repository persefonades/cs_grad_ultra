#include <iostream>

using namespace std;


int main(int argc, char const *argv[])
{
	int a[10] = {5, 9, 6, 3, 7, 1, 6, 0, 8, 10};
	int v = 7, i = -1;
	for (int j = 1; j < 10; ++j)
	{
		if (a[j] == v) {
			i = j;
			break;
		}
	}

	cout << i << endl;

	return 0;
}