#include <iostream>

using namespace std;

void merge(int *a, int p, int q, int r) {
	int n1 = q - p + 1, n2 = r - q, i, j, k;
	int L[n1], R[n2];
	for (i = 0; i < n1; ++i)
		L[i] = a[p + i];
	for (j = 0; j < n2; ++j)
		R[j] = a[q + j + 1];
	i = j = 0;
	k = p;
	while (i != n1 && j != n2) {
		if (L[i] <= R[j])
			a[k] = L[i++];
		else
			a[k] = R[j++];
		k++;
	}
	if (i == n1) {
		for (int m = j; m < n2; ++m)
			a[k++] = R[m];
	}
	if (j == n2) {
		for (int m = i; m < n1; ++m)
			a[k++] = L[m];
	}
}

void insertionSort(int *a, int p, int r) {
	for (int i = p + 1; i <= r; ++i)
	{
		int key = a[i];
		int j = i - 1;
		while (j >= p && a[j] > key) {
			a[j + 1] = a[j];
			j = j - 1;
		}
		a[j + 1] = key;
	}
}

void split(int *a, int p, int r, int k) {
	if(p-r<k){
		insertionSort(a,p,r);
		return;
	}
	if (p < r) {
		int q = (p + r) / 2;
		split(a, p, q, k);
		split(a, q + 1, r, k);
		merge(a, p, q, r);
	}
}


int main(int argc, char const *argv[])
{
	int a[10] = {5, 9, 6, 3, 7, 1, 6, 0, 8, 10};
	split(a, 0, 9, 4);
	for (int i = 0; i < 10; ++i)
		cout << a[i] << " ";
	cout << endl;
	return 0;
}