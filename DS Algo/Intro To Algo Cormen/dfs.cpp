#include <iostream>
#include <vector>
#include "graph.h"

using namespace std;

void DFS_visit(node* u);

int timer = 0;

void DFS(graph G) {
	std::vector<node*> nodes = G.nodes;
	for (int i = 0; i < nodes.size(); i++)
		DFS_visit(G.nodes[i]);
}

void DFS_visit(node* u) {
	if (u->visited) return;

	u->visited = true;
	u->visit = timer++;
	cout << u->data << " ";

	vector<node*> neighbours = u->neighbours;
	for ( node* next : neighbours) {
		DFS_visit(next);
	}
}

int main(int argc, char const *argv[])
{
	std::vector<node*> nodes;
	for (int i = 0; i <= 12; ++i)
		nodes.push_back(new node(i));
	graph G(nodes);

	G.addEdge(0, 1);
	G.addEdge(0, 9);
	G.addEdge(1, 8);
	G.addEdge(9, 8);
	G.addEdge(8, 7);
	G.addEdge(7, 10);
	G.addEdge(10, 11);
	G.addEdge(11, 7);
	G.addEdge(7, 6);
	G.addEdge(7, 3);
	G.addEdge(3, 5);
	G.addEdge(6, 5);
	G.addEdge(3, 2);
	G.addEdge(3, 4);

	cout << "DFS Traversal" << endl;
	DFS(G);
	cout << endl;
	
	G.display();
	return 0;
}
