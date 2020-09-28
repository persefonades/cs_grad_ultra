#include <iostream>
#include <vector>
#include "graph.h"

using namespace std;

int id = 0;

vector<int> ids, lows;

vector<edge*> dfs(graph G, int at, int parent, vector<edge*> bridges) {
	node* u = G.nodes[at];
	u->visited = true;
	lows[at] = ids[at] = ++id;
	for ( node* to : u->neighbours) {
		if (to->data == parent) continue;
		if (!to->visited) {
			bridges = dfs(G, to->data, at, bridges);
			lows[at] = min(lows[at], lows[to->data]);
			if (ids[at] < lows[to->data])
				bridges.push_back(G.getEdge(u, G.nodes[to->data]));
		} else
			lows[at] = min(lows[at], ids[to->data]);
	}

	return bridges;
}

vector<edge*> findBridges(graph G) {
	vector<edge*> bridges;
	int n = G.nodes.size(), i;
	for (i = 0; i < n; i++) {
		if (!G.nodes[i]->visited)
			bridges = dfs(G, i, -1, bridges);
	}
	return bridges;
}

int main(int argc, char const *argv[])
{
	int i;
	vector<node*> nodes;
	for (i = 0; i < 9; ++i)
		nodes.push_back(new node(i));
	graph G(nodes);

	G.addEdge(0, 1);
	G.addEdge(1, 2);
	G.addEdge(2, 0);
	G.addEdge(2, 3);
	G.addEdge(3, 4);
	G.addEdge(2, 5);
	G.addEdge(5, 6);
	G.addEdge(6, 7);
	G.addEdge(7, 8);
	G.addEdge(8, 5);

	G.display();

	for (i = 0; i < 9; i++) {
		ids.push_back(0);
		lows.push_back(0);
	}

	vector<edge*> bridges = findBridges(G);
	cout << "Bridges:" << endl;
	for (edge* e : bridges)
	{
		cout << "from " << e->v1->data << " to " << e->v2->data << endl;
	}

	return 0;
}