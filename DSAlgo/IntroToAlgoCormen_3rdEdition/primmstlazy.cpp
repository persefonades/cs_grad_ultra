#include <iostream>
#include <vector>
#include <functional>
#include <queue>
#include "graph.h"

using namespace std;

auto cmp = [](edge* a, edge* b) {return a->cost > b->cost;};

priority_queue<edge*, vector<edge*>, decltype(cmp)> pq(cmp);

void addEdges(graph G, node* i) {
	i->visited = true;

	vector<edge*> edges = G.getEdges(i);
	for (edge* e : edges) {
		if (!e->v2->visited)
			pq.push(e);
	}
}

vector<edge*> lazyPrims(graph G, node* s) {
	int m = G.nodes.size() - 1, edgeCount = 0;
	vector<edge*> mstEdges(m);
	addEdges(G, s);

	while (!pq.empty() && edgeCount != m) {
		edge* e = pq.top();
		pq.pop();
		node* n = e->v2;
		if (n->visited)
			continue;

		mstEdges[edgeCount++] = e;
		addEdges(G, n);
	}

	if (edgeCount != m)
		return vector<edge*> {};

	return mstEdges;
}


int main(int argc, char const *argv[])
{
	vector<node*> nodes;
	for (int i = 0; i < 8; ++i)
		nodes.push_back(new node(i));
	graph G(nodes);

	G.addDirectedEdge(0, 1, 10);
	G.addDirectedEdge(0, 2, 1);
	G.addDirectedEdge(0, 3, 4);

	G.addDirectedEdge(2, 1, 3);
	G.addDirectedEdge(2, 5, 8);
	G.addDirectedEdge(2, 3, 2);
	G.addDirectedEdge(2, 0, 1);

	G.addDirectedEdge(3, 2, 2);
	G.addDirectedEdge(3, 5, 2);
	G.addDirectedEdge(3, 6, 7);
	G.addDirectedEdge(3, 0, 4);

	G.addDirectedEdge(5, 2, 8);
	G.addDirectedEdge(5, 4, 1);
	G.addDirectedEdge(5, 7, 9);
	G.addDirectedEdge(5, 6, 6);
	G.addDirectedEdge(5, 3, 2);

	G.addDirectedEdge(4, 1, 0);
	G.addDirectedEdge(4, 5, 1);
	G.addDirectedEdge(4, 7, 8);

	G.addDirectedEdge(1, 0, 10);
	G.addDirectedEdge(1, 2, 3);
	G.addDirectedEdge(1, 4, 0);

	G.addDirectedEdge(6, 3, 7);
	G.addDirectedEdge(6, 5, 6);
	G.addDirectedEdge(6, 7, 12);

	G.addDirectedEdge(7, 4, 8);
	G.addDirectedEdge(7, 5, 9);
	G.addDirectedEdge(7, 6, 12);

	G.display();

	vector<edge*> mstEdges = lazyPrims(G, G.nodes[0]);
	int mstCost = 0;
	if (mstEdges.size())
	{
		cout << "MST Edges: " << endl;
		for (edge* e : mstEdges)
		{
			e->display();
			mstCost += e->cost;
		}

		cout << "MST Cost: " << mstCost << endl;
	} else {
		cout << "No MST possible" << endl;
	}
	return 0;
}