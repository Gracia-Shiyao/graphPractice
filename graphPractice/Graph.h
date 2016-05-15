#pragma once
#include <list>
#include <utility>

class Graph {
protected:
	int V;
	std::list<std::pair<int, int>> *adj;
public:
	Graph(int v) :V(v) { adj = new std::list<std::pair<int, int>>[v]; }
	virtual void addEdge(int u, int v, int w) = 0; //make addEdge class  
};

