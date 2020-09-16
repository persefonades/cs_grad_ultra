#include <iostream>

using namespace std;

int binSearch(int *a, int l, int r, int v) {
	if (l > r)
		return -1;
	int m = (l + r) / 2;
	if (a[m] == v)
		return m;
	if (a[m] < v)
		return binSearch(a, l, m, v);
	return binSearch(a, m + 1, r, v);
}

int main(int argc, char const *argv[])
{
	int a[10] = {5, 9, 6, 3, 7, 1, 6, 0, 8, 10};

	cout << binSearch(a, 0, 9, 5) << endl;

	return 0;
}