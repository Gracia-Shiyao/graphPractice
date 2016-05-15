#include <iostream>
#include <queue>
#include <set>
#include <utility>
#include <climits>
#include <cstdio>
#include "Graph.h"


using namespace std;

class UndirectedGraph : protected Graph {
	//bool isCyclicUtil(int v, bool visited[], int parent);
public:
	UndirectedGraph(int v) :Graph(v) {};
	void addEdge(int u, int v, int w);
	//bool isCyclic(); //return true if there is cycle in graph
	//bool isReachable(int s, int d);
	void shortestPath(int s);
};

void UndirectedGraph::addEdge(int u, int v, int w) {
	adj[u].push_back(make_pair(v, w));
	adj[v].push_back(make_pair(u, w));
}

void UndirectedGraph::shortestPath(int s) {
	//create a set to store vertices that are being preprocessed
	set< pair<int, int> > setds;
	//vector for distances adn initialize its all distance to intmax
	vector<int> dist(V, INT_MAX);
	//insert source to the set and initialize its distance as 0
	setds.insert(make_pair(0, s));
	dist[s] = 0;

	//begin loop
	while (!setds.empty()) {
		//the first vertex in set is the minimum distance vertex, extract it from set
		pair<int, int> tmp = *(setds.begin());
		setds.erase(setds.begin());
		//vertex u with weight tmp.first
		int u = tmp.second;
		list<pair<int, int>>::iterator i;
		for (i = adj[u].begin(); i != adj[u].end(); ++i) {
			int v = (*i).first;
			int weight = (*i).second;

			if (dist[v] > dist[u] + weight) {
				if (dist[v] != INT_MAX)
					setds.erase(setds.find(make_pair(dist[v], v)));
				dist[v] = dist[u] + weight;
				setds.insert(make_pair(dist[v], v));
			}
		}
	}//end while loop

	printf("vertex distance from source\n");
	for (int i = 0; i < V; ++i) {
		printf("%d \t\t %d\n", i, dist[i]);
	}
}
/*
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
*/
/*
int main() {
	UndirectedGraph g{ 9 };
	g.addEdge(0, 1, 4);
	g.addEdge(0, 7, 8);
	g.addEdge(1, 2, 8);
	g.addEdge(1, 7, 11);
	g.addEdge(2, 3, 7);
	g.addEdge(2, 8, 2);
	g.addEdge(2, 5, 4);
	g.addEdge(3, 4, 9);
	g.addEdge(3, 5, 14);
	g.addEdge(4, 5, 10);
	g.addEdge(5, 6, 2);
	g.addEdge(6, 7, 1);
	g.addEdge(6, 8, 6);
	g.addEdge(7, 8, 7);

	g.shortestPath(0);
	return 0;
	*/
	/*
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
		
		*/