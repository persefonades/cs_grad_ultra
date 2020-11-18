#include <iostream>

using namespace std;

int countInv(int *a, int p, int q, int r)
{
	int inv = 0, n1 = q - p + 1, n2 = r - q, i, j, k;
	int L[n1], R[n2];
	for (i = 0; i < n1; ++i)
		L[i] = a[p + i];
	for (j = 0; j < n2; ++j)
		R[j] = a[q + j + 1];
	i = j = 0;
	k = p;
	while (i != n1 && j != n2) {
		if (L[i] <= R[j]) {
			a[k] = L[i];
			i++;
		} else {
			a[k] = R[j];
			inv += j + 1;
			j++;
		}
		k++;
	}
	if (i == n1) {
		for (int m = j; m < n2; ++m) {
			a[k] = R[m];
			k++;
		}
	}
	if (j == n2) {
		for (int m = i; m < n1; ++m) {
			a[k] = L[m];
			inv +=  n2;
			k++;
		}
	}
	return inv;
}

int inversions(int *a, int p, int r)
{
	if (p < r) {
		int q = (p + r) / 2;
		int left = inversions(a, p, q);
		int right = inversions(a, q + 1, r);
		int inv = countInv(a, p, q, r) + left + right;
		return inv;
	}
	return 0;
}


int main(int argc, char const *argv[])
{
	// int a[10] = {5, 9, 6, 3, 7, 1, 6, 0, 8, 10};
	int a[5] = {2, 3, 9, 2, 9};
	cout << inversions(a, 0, 4) << endl;
	return 0;
}