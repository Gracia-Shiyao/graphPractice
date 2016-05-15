#include <iostream>
#include <list>
#include <queue>
#include <stack>
using namespace std;

class Graph {
	int V; //No. of vertex
	list<int> * adj;
	void DFSUtil(int v, bool visited[]);
	void topoSortUtil(int v, bool visited[], stack<int>& S);
public:
	Graph(int v);
	void addEdge(int v, int w);
	void DFS(int v); //start point of dfs
	void DFS();
	void BFS(int v); //start with vertex v
	void topologicalSort();
};

Graph::Graph(int v) {
	this->V = v;
	adj = new list<int>[v];
}

void Graph::addEdge(int v, int w) {
	adj[v].push_back(w);
}

void Graph::DFSUtil(int v, bool visited[]) {
	//Mark the current node as visitd and print it
	visited[v] = true;
	cout << v << " ";
	//recursive for all the vertices adjacent to this vertex
	list<int>::iterator i;
	for (i = adj[v].begin(); i != adj[v].end(); ++i) {
		if (!visited[*i]) {
			DFSUtil(*i, visited);
		}
	}
}

void Graph::DFS(int v) {
	bool *visited = new bool[V];
	for (int i = 0; i < V; ++i) {
		visited[i] = false;
	}
	DFSUtil(v, visited);
}

void Graph::DFS() {
	bool * visited = new bool[V];
	for (int i = 0; i < V; ++i) {
		visited[i] = false;
	}
	for (int i = 0; i < V; ++i) {
		if (visited[i] == false) {
			DFSUtil(i, visited);
		}
	}
}

void Graph::BFS(int s) {
	//mark all vertex as not visited
	bool * visited = new bool[V];
	for (int i = 0; i < V; ++i) {
		visited[i] = false;
	}
	queue<int> q;
	q.push(s);
	list<int>::iterator i; //used for iterate v's adjacent set

	while (!q.empty()) {
		//dequeue a vertex from queue and print it
		s = q.front();
		cout << s << " ";
		q.pop();
		//get all adjacent vertices of the s 
		//if a adjacent has not been visited, marked and enqueue
		for (i = adj[s].begin(); i != adj[s].end(); ++i) {
			if (!visited[*i]) {
				visited[*i] = true;
				q.push(*i);
			}
		}
	} //enddo
}
/*In recursive topoSort method, for each vertex v, first we recursively call
  topoSortUtil on its adjcent vertex which are not visited yet, push them into stack.
  After reviewing all adjacent vertex, push the vertex v into stack.
*/
void Graph::topoSortUtil(int v, bool visited[], stack<int>& stk) {
	visited[v] = true;

	list<int>::iterator i;
	for (i = adj[v].begin(); i != adj[v].end(); ++i) {
		if (!visited[*i]) {
			topoSortUtil(*i, visited, stk);
		}
	}

	stk.push(v);
}
/*in recursive topoSort method, initialize the stack, then call the recursive helper function
  to store Topological Sort start from all vertices one-by-one*/
void Graph::topologicalSort() {
	stack<int> stk;

	bool * visited = new bool[V];
	for (int i = 0; i < V; ++i) {
		visited[i] = false;
	}

	//call the utils
	for (int i = 0; i < V; i++) {
		if (visited[i] == false) {
			topoSortUtil(i, visited, stk);
		}
	}

	//print content of stack
	while (!stk.empty()) {
		cout << stk.top() << " ";
		stk.pop();
	}
}
int main() {
	Graph g{ 6 };
	g.addEdge(5, 2);
	g.addEdge(5, 0);
	g.addEdge(4, 0);
	g.addEdge(4, 1);
	g.addEdge(2, 3);
	g.addEdge(3, 1);

	cout << "\n DFS1:\n";
	g.DFS(2);
	cout << "\n DFS2:\n";
	g.DFS();
	cout << "\n BFS:\n";
	g.BFS(2);
	cout << "\n Topological Sort: \n";
	g.topologicalSort();
}