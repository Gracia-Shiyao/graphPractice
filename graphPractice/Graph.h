#pragma once
#include <list>

class Graph {
protected:
	int V;
	std::list<int> *adj;
public:
	Graph(int v) :V(v) { adj = new std::list<int>[v]; }
	virtual void addEdge(int v, int w) = 0; //make addEdge class  
};

