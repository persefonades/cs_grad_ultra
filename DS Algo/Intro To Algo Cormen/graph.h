#ifndef GRAPH
#define GRAPH
#include<iostream>
#include<vector>

class node {
public:
	int data, visit;
	bool visited;
	std::vector<node*> neighbours;
	std::vector<node*> leaving;
	std::vector<node*> coming;
	node *next, *prev;
	node(int data, int visit = 0, std::vector<node*> neighbours = {}) {
		this->data = data;
		this->visit = visit;
		this->visited = false;
		this->neighbours = neighbours;
		this->next = NULL;
		this->prev = NULL;
	}
};

class edge {
public:
	node *v1, *v2;
	int cost;
	bool type;
	edge(node *v1, node *v2, int cost, bool type = 0) {
		this->v1 = v1;
		this->v2 = v2;
		this->cost = cost;
		this->type = type;
	}
};

class graph {
public:
	std::vector<node*> nodes;
	std::vector<edge*> edges;
	graph(std::vector<node*> nodes) {
		this->nodes = nodes;
	}
	void display() {
		for (node* n : nodes)
		{
			if (n) {
				std::cout << n->data;
				if (n->neighbours.size()) {
					std::cout << " =>(";
					display(n->neighbours);
					std::cout << ") ";
				}
				if (n->leaving.size()) {
					std::cout << " =>(";
					display(n->leaving);
					std::cout << ") ";
				}
				if (n->coming.size()) {
					std::cout << " =>(";
					display(n->coming);
					std::cout << ") ";
				}
				std::cout << " : " << n->visit << std::endl;
			}
		}
	}
	void display(std::vector<node*> v) {
		if (!v.size())
			return;
		for (node* n : v)
		{
			if (n)
				std::cout << " " << n->data;
		}
	}
	node* getNode(int data) {
		for (node* n : nodes)
		{
			if (n->data == data)
				return n;
		}
		return NULL;
	}

	edge* getEdge(node* v1, node* v2) {
		for (edge* e : edges)
		{
			if (e->v1 == v1 && e->v2 == v2)
				return e;
		}
		return NULL;
	}
	void addEdge(int v1, int v2, int cost = 0) {
		node *vn1 = getNode(v1), *vn2 = getNode(v2);
		vn1->neighbours.push_back(vn2);
		vn2->neighbours.push_back(vn1);
		edges.push_back(new edge(vn1, vn2, cost));
	}
	void addDirectedEdge(int v1, int v2, int cost = 0) {
		node *vn1 = getNode(v1), *vn2 = getNode(v2);
		vn1->leaving.push_back(vn2);
		vn2->coming.push_back(vn1);
		edges.push_back(new edge(vn1, vn2, cost, 1));
	}
};

#endif