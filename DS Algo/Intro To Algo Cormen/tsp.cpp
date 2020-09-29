#include <iostream>
#include <vector>

#define N 4

using namespace std;

void combinations(int set, int at,
                  int r, int n, vector<int> &subsets) {
	// Return early if there are more elements left to select than what is available.
	int elementsLeftToPick = n - at;
	if (elementsLeftToPick < r) return;

	if (r == 0) {
		subsets.push_back(set);
	} else {
		for (int i = at; i < n; i++) {
			set ^= (1 << i);
			combinations(set, i + 1, r - 1, n, subsets);
			set ^= (1 << i);
		}
	}
}

vector<int> combinations(int r, int n) {
	vector<int> subsets;
	combinations(0, 0, r, n, subsets);
	return subsets;
}

int notIn(int i, int subset) {
	return ((1 << i) & subset) == 0;
}

int main(int argc, char const *argv[])
{
	int S = 0;
	int m[N][N] = {
		{0, 4, 1, 9},
		{3, 0, 6, 11},
		{4, 1, 0, 2},
		{6, 5, -4, 0}
	};
	int i, j;
	int memo[N][1 << N];

	int END_STATE = (1 << N) - 1;

	for (i = 0; i < N; ++i)
		for (j = 0; j < (1 << N); ++j)
			memo[i][j] = 0;


	// Setup
	for (i = 0; i < N; ++i) {
		if (i == S) continue;
		memo[i][(1 << S) | (1 << i)] = m[S][i];
	}

	// Solve
	for (int r = 3; r <= N; r++) {
		for (int subset : combinations(r, N)) {
			if (notIn(S, subset)) continue;
			for (int next = 0; next < N; next++) {
				if (next == S || notIn(next, subset)) continue;
				int state = subset ^ (1 << next);
				int minDist = 99999;
				for (int e = 0; e < N; e = e + 1) {
					if (e == S || e == next || notIn(e, subset)) continue;
					int newDistance = memo[e][state] + m[e][next];
					if (newDistance < minDist) minDist = newDistance;
				}
				memo[next][subset] = minDist;
			}
		}
	}

	// Find Min Cost
	int minTourCost = 99999;

	for (int e = 0; e < N; e++) {
		if (e == S) continue;
		int tourCost = memo[e][END_STATE] + m[e][S];
		if (tourCost < minTourCost)
			minTourCost = tourCost;
	}

	cout << minTourCost << endl;
	// Find Optimal Tour
	int lastIndex = S;
	int state = (1 << N) - 1;
	vector<int> tour(N + 1);

	for (i = N - 1; i >= 1; i--) {
		int index = -1;
		for (j = 0; j < N; j++) {
			if (j == S || notIn(j, state)) continue;
			if (index == -1) index = j;
			int prevDist = memo[index][state] + m[index][lastIndex];
			int newDist = memo[j][state] + m[j][lastIndex];
			if (newDist < prevDist) index = j;
		}
		tour[i] = index;
		state = state ^ (1 << index);
		lastIndex = index;
	}
	tour[0] = tour[N] = S;

	for (int i = 0; i < N; ++i)
		cout << tour[i] << "=>";
	cout << tour[N] << endl;


	return 0;
}