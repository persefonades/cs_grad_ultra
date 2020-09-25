#ifndef GRAPH
#define GRAPH
#include<iostream>
#include<vector>

class node {
public:
	int data, visit;
	bool visited;
	std::vector<node*> neighbours;
	node(int data, int visit = 0, std::vector<node*> neighbours = {}) {
		this->data = data;
		this->visit = visit;
		this->visited = false;
		this->neighbours = neighbours;
	}
};

class graph {
public:
	std::vector<node*> nodes;
	graph(std::vector<node*> nodes) {
		this->nodes = nodes;
	}
	void display() {
		for (node* n : nodes)
		{
			if (n) {
				std::cout << n->data << " =>(";
				display(n->neighbours);
				std::cout << ")" << std::endl;
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
	void addVertex(int v1, int v2) {
		node *vn1 = getNode(v1), *vn2 = getNode(v2);
		vn1->neighbours.push_back(vn2);
		vn2->neighbours.push_back(vn1);
	}
};

#endif