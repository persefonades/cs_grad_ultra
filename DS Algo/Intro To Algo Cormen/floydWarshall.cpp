#include <iostream>
#include <queue>
#include <limits>
#include <vector>

// #define INF 99999
#define N 7

using namespace std;


int i, j, k;
int _next[N][N] = {0};
double dp[N][N] = {0};
const double POSITIVE_INFINITY = std::numeric_limits<double>::infinity();
const double NEGATIVE_INFINITY = -std::numeric_limits<double>::infinity();
// int m[N][N] = {
// 	{0, 4, 1, INF},
// 	{INF, 0, 6, INF},
// 	{4, 1, 0, 2},
// 	{INF, INF, INF, 0}
// };

double m[N][N] = {0};

void setup() {
	// Setup
	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			if (m[i][j] != POSITIVE_INFINITY) _next[i][j] = j;
			dp[i][j] = m[i][j];
		}
	}
}

void propagateNegativeCycles() {
	int i, j, k;
	// Propagate Negative Cycles
	for (k = 0; k < N; k++)
		for (i = 0; i < N; i++)
			for (j = 0; j < N; j++)
				if (dp[i][k] + dp[k][j] < dp[i][j]) {
					dp[i][j] = NEGATIVE_INFINITY;
					_next[i][j] = -1;
				}
}


void floydWarshall() {
	setup();

	// Shortest Path Algo
	for (k = 0; k < N; k++)
		for (i = 0; i < N; i++)
			for (j = 0; j < N; j++)
				if (dp[i][k] + dp[k][j] < dp[i][j]) {
					dp[i][j] = dp[i][k] + dp[k][j];
					_next[i][j] = _next[i][k];
				}


	propagateNegativeCycles();
}


vector<int> reconstructPath(int start, int end) {
	vector<int> path(0);
	int at = start;
	if (dp[start][end] == POSITIVE_INFINITY) return path;
	for (; at != end; at = _next[at][end]) {
		if (at == -1) return vector<int> {};
		path.push_back(at);
	}
	if (_next[at][end] == -1) return vector<int> {};
	path.push_back(end);
	return path;
}


int main(int argc, char const *argv[])
{
	for (i = 0; i < N; i++)
		for (j = 0; j < N; j++)
			m[i][j] = POSITIVE_INFINITY;
	for (i = 0; i < N; i++)
		m[i][i] = 0;


	m[0][1] = 2;
	m[0][2] = 5;
	m[0][6] = 10;
	m[1][2] = 2;
	m[1][4] = 11;
	m[2][6] = 2;
	m[6][5] = 11;
	m[4][5] = 1;
	m[5][4] = -2;

	floydWarshall();
	cout << "Source List" << endl;
	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++)
			if (i != j) {
				printf("%5d -> %5d = ", i, j);
				cout << (dp[i][j] == POSITIVE_INFINITY ?
				         "INF" : dp[i][j] == NEGATIVE_INFINITY ?
				         "-INF" : to_string((int)dp[i][j])) << " (";
				vector<int> path = reconstructPath(i, j);
				for (int i : path) {
					printf("%3d", i);
				}
				cout << ")" << endl;
			}
	}

	return 0;
}