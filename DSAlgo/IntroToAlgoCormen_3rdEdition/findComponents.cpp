#include <iostream>
#include <vector>
#include "graph.h"

using namespace std;

void dfs(node* u);

int count = 0;
void findComponents(graph G) {
	for (node* n : G.nodes) {
		if (!n->visited) {
			dfs(n);
			count++;
		}
	}
}

void dfs(node* u) {
	u->visited = true;
	u->visit = count;
	vector<node*> neighbours = u->neighbours;
	for ( node* next : neighbours) {
		if (!next->visited)
			dfs(next);
	}
}

int main(int argc, char const *argv[])
{
	std::vector<node*> nodes;
	for (int i = 0; i < 18; ++i)
		nodes.push_back(new node(i));
	graph G(nodes);

	// Component 1
	G.addVertex(6, 11);
	G.addVertex(7, 11);
	G.addVertex(6, 7);

	G.addVertex(1, 5);
	G.addVertex(5, 17);
	G.addVertex(5, 16);

	G.addVertex(0, 4);
	G.addVertex(0, 13);
	G.addVertex(0, 8);
	G.addVertex(0, 14);
	G.addVertex(4, 8);
	G.addVertex(8, 14);
	G.addVertex(13, 14);

	G.addVertex(3, 9);
	G.addVertex(9, 15);
	G.addVertex(9, 2);
	G.addVertex(2, 15);
	G.addVertex(10, 15);

	cout << "Graph Components" << endl;
	findComponents(G);
	G.display();

	return 0;
}