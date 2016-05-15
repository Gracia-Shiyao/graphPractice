#include <iostream>
#include <queue>
#include "Graph.h"

using namespace std;

class UndirectedGraph : protected Graph {
	bool isCyclicUtil(int v, bool visited[], int parent);
public:
	UndirectedGraph(int v) :Graph(v) {};
	void addEdge(int v, int w);
	bool isCyclic(); //return true if there is cycle in graph
	bool isReachable(int s, int d);
};

void UndirectedGraph::addEdge(int v, int w) {
	adj[v].push_back(w);
	adj[w].push_back(v);
}

bool UndirectedGraph::isCyclicUtil(int v, bool visited[], int parent) {
	visited[v] = true;
	list<int>::iterator i;
	for (i = adj[v].begin(); i != adj[v].end(); ++i) {
		//if an adjacent is not visited, the recur for that adjacent
		if (!visited[*i]) {
			if (isCyclicUtil(*i, visited, v)) {
				return true;
			}
		}
		else if (*i != parent) 
			return true;
	}
	return false;
}

bool UndirectedGraph::isCyclic() {
	//mark all vertices as not visited

bool* visited = new bool[V];

	for (int i = 0; i < V; i++) {
		visited[i] = false;
	}

	for (int u = 0; u < V; ++u) {
		if (!visited[u])
			if (isCyclicUtil(u, visited, -1))
				return true;
	}

	return false;
}

bool UndirectedGraph::isReachable(int s, int d) {
	if (s == d) return true;

	bool * visited = new bool[V];
	for (int i = 0; i < V; ++i) {
		visited[i] = false;
	}
	//queue for BFS
	queue<int> q;

	visited[s] = true;
	q.push(s);

	list<int>::iterator i;
	while (!q.empty()) {
		s = q.front();
		q.pop();

		for (i = adj[s].begin(); i != adj[s].end(); ++i) {
			if (*i == d)
				return true;
			//else, continue to do BFS
			if (!visited[*i]) {
				visited[*i] = true;
				q.push(*i);
			}
		}
	}
	return false;
}
int main() {
	UndirectedGraph g{ 5 };
	g.addEdge(0, 1);
	g.addEdge(0, 2);
	g.addEdge(2, 0);
	g.addEdge(0, 3);
	g.addEdge(3, 4);
	
	bool isC = g.isCyclic();
	cout << "\n IsCyclic? \n";
	if (isC)
		cout << "Yes";
	else
		cout << "No";

	bool isR = g.isReachable(0, 3);
	cout << "is 0, 3 reachable?\n";
	if (isR)
		cout << "Yes\n"; 
	else
		cout << "No\n";
}