#include <iostream>
#include "Graph.h"

using namespace std;

class UndirectedGraph : protected Graph {
public:
	UndirectedGraph(int v) :Graph(v) {};
	void addEdge(int v, int w);
};

void UndirectedGraph::addEdge(int v, int w) {
	adj[v].push_back(w);
	adj[w].push_back(v);
}

