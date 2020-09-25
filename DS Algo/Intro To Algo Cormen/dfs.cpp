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
	nodes.push_back(new node(0));
	nodes.push_back(new node(1));
	nodes.push_back(new node(9));
	nodes.push_back(new node(8));
	nodes.push_back(new node(7));
	nodes.push_back(new node(10));
	nodes.push_back(new node(11));
	nodes.push_back(new node(6));
	nodes.push_back(new node(5));
	nodes.push_back(new node(4));
	nodes.push_back(new node(3));
	nodes.push_back(new node(2));
	graph G(nodes);

	G.addVertex(0, 1);
	G.addVertex(0, 9);
	G.addVertex(1, 8);
	G.addVertex(9, 8);
	G.addVertex(8, 7);
	G.addVertex(7, 10);
	G.addVertex(10, 11);
	G.addVertex(11, 7);
	G.addVertex(7, 6);
	G.addVertex(7, 3);
	G.addVertex(3, 5);
	G.addVertex(6, 5);
	G.addVertex(3, 2);
	G.addVertex(3, 4);

	G.display();

	cout << "DFS Traversal" << endl;
	DFS(G);
	cout << endl;
	
	return 0;
}
