#include <iostream>
#include <algorithm>

using namespace std;

bool findSum(int *a, int n, int s) {
	int i = 0, j = n - 1;
	while (i < j) {
		if ((a[i] + a[j]) == s)
			return true;
		if (a[i] + a[j] < s)
			i++;
		if (a[i] + a[j] > s)
			j--;
	}
	return false;
}

int main(int argc, char const *argv[])
{
	int a[10] = {5, 9, 6, 3, 7, 1, 6, 0, 8, 10};
	sort(a, a + 10);
	cout << (findSum(a, 10, 2) ? "True" : "False") << endl;
	return 0;
}