#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include "graph.h"

using namespace std;

void solve(node* u);
vector<node*> reconstructPath(graph, int, int);

int timer = 0;

vector<node*> BFS(graph G, int s = 0, int e = -1) {
	vector<node*> nodes = G.nodes;
	if (e == -1)
		e = G.nodes.size() - 1;
	solve(G.nodes[s]);
	return reconstructPath(G, s, e);
}

void solve(node* u) {
	queue<node*> q;
	q.push(u);

	u->visited = true;
	u->visit = timer++;
	cout << u->data << " ";

	while (!q.empty()) {
		node* curr = q.front();
		q.pop();
		vector<node*> neighbours = curr->neighbours;
		for ( node* next : neighbours) {
			if (!next->visited) {
				q.push(next);
				cout << next->data << " ";
				next->visited = true;
				next->visit = timer++;
				next->prev = curr;
			}
		}
	}
}

vector<node*> reconstructPath(graph G, int s = 0, int e = -1) {
	vector<node*> path;
	if (e == -1)
		e = G.nodes.size() - 1;
	node* curr = G.nodes[e];
	while (curr) {
		if (!curr)
			break;
		path.push_back(curr);
		curr = curr->prev;
	}
	reverse(path.begin(), path.end());
	if (path[0] == G.nodes[s])
		return path;

	return vector<node*> {};
}

int main(int argc, char const *argv[])
{
	vector<node*> nodes;
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

	cout << "BFS Traversal" << endl;
	vector<node*> path = BFS(G, 0, 2);
	cout << endl;

	G.display();

	if (path.size()) {
		for (int i = 0; i < path.size(); i++) {
			if (path[i]) {
				cout << path[i]->data << " ";
			}
		}
	} else{
		cout<<"No valid path available";
	}
	cout << endl;
	return 0;
}
