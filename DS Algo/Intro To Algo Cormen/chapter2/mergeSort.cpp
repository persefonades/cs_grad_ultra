#include <iostream>

using namespace std;

void merge(int *a, int p, int q, int r) {
	int n1 = q - p + 1, n2 = r - q, i, j;
	int L[n1 + 1], R[n2 + 1];
	for (int i = 0; i < n1; ++i)
		L[i] = a[p + i];
	for (int j = 0; j < n2; ++j)
		R[j] = a[q + j + 1];
	L[n1] = R[n2] = 999999;
	i =  j = 0;
	for (int k = p; k <= r; ++k)
	{
		if (L[i] <= R[j])
			a[k] = L[i++];
		else
			a[k] = R[j++];
	}
}

void mergeSort(int *a, int p, int r) {
	if (p < r) {
		int q = (p + r) / 2;
		mergeSort(a, p, q);
		mergeSort(a, q + 1, r);
		merge(a, p, q, r);
	}
}

int main(int argc, char const *argv[])
{
	int a[10] = {5, 9, 6, 3, 7, 1, 6, 0, 8, 10};
	mergeSort(a, 0, 9);
	for (int i = 0; i < 10; ++i)
		cout << a[i] << " ";
	cout << endl;

	return 0;
}