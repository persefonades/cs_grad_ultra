#include <iostream>
#include <vector>
#include "graph.h"

using namespace std;

vector<int> in, out;
vector<node*> path;

void countInOutDegrees(graph G) {
	for (int i = 0; i < G.nodes.size(); ++i)
	{
		in.push_back(G.nodes[i]->coming.size());
		out.push_back(G.nodes[i]->leaving.size());
	}
}

bool graphHasEulerianPath(graph G) {
	int startNode = 0, endNode = 0, i;
	for (i = 0; i < G.nodes.size(); i++) {
		if ((out[i] - in[i]) > 1 || (in[i] - out[i]) > 1)
			return false;
		if ((out[i] - in[i]) == 1)
			startNode++;
		else if ((in[i] - out[i]) == 1)
			endNode++;
	}
	return ((endNode == 0 && startNode == 0) || (endNode == 1 && startNode == 1));
}

void dfs(graph G, int at) {
	while (out[at] != 0) {
		node* next_node = G.nodes[at]->leaving[--out[at]];
		dfs(G, next_node->data);
	}
	path.insert(path.begin(), G.nodes[at]);
}

int findStartNode(graph G) {
	int start = 0, i;
	for (i = 0; i < G.nodes.size(); i++) {
		if (out[i] - in[i] == 1) return i;
		if (out[i] > 0) start = i;
	}
	return start;
}

void findEulerianPath(graph G) {
	int m = G.edges.size();
	countInOutDegrees(G);

	if (!graphHasEulerianPath(G)) return;

	dfs(G, findStartNode(G));

	if (path.size() == m + 1) return;
}

int main(int argc, char const *argv[])
{
	int i;
	vector<node*> nodes;
	for (i = 0; i < 7; ++i)
		nodes.push_back(new node(i));
	graph G(nodes);

	G.addDirectedEdge(1, 2);
	G.addDirectedEdge(1, 3);
	G.addDirectedEdge(2, 2);
	G.addDirectedEdge(2, 4);
	G.addDirectedEdge(2, 4);
	G.addDirectedEdge(3, 1);
	G.addDirectedEdge(3, 2);
	G.addDirectedEdge(3, 5);
	G.addDirectedEdge(4, 3);
	G.addDirectedEdge(4, 6);
	G.addDirectedEdge(5, 6);
	G.addDirectedEdge(6, 3);

	// G.addDirectedEdge(0, 1);
	// G.addDirectedEdge(1, 2);
	// G.addDirectedEdge(1, 4);
	// G.addDirectedEdge(1, 3);
	// G.addDirectedEdge(2, 1);
	// G.addDirectedEdge(4, 1);

	G.display();

	findEulerianPath(G);

	for (node* n : path) {
		cout << n->data << " ";
	}
	cout << endl;
	return 0;
}