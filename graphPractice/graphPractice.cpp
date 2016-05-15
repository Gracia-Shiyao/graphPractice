#include <iostream>
#include <list>
#include <queue>
#include <stack>
#include <vector>
using namespace std;

class Graph {
	int V; //No. of vertex
	list<int> * adj;
	void DFSUtil(int v, bool visited[]);
//	void topoSortUtil(int v, bool visited[], stack<int>& S);
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
/*
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
*/
/*in recursive topoSort method, initialize the stack, then call the recursive helper function
  to store Topological Sort start from all vertices one-by-one*/
/*
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
*/
/*Kahn's algorithm for topological sort*/
void Graph::topologicalSort() {
	//create a vector to store in-degree of all vertices. Initialize all 0
	vector<int> in_degree(V, 0);

	//to fill the indegree of vertices
	for (int u = 0; u < V; ++u) {
		list<int>::iterator iter;
		for (iter = adj[u].begin(); iter != adj[u].end(); ++iter) {
			in_degree[*iter]++;
		}
	}

	//create a queue and enqueue all vertices with 0 indegree
	queue<int> q;
	for (int i = 0; i < V; i++) {
		if (in_degree[i] == 0)
			q.push(i);
	}
	//count of visited vertex
	int cnt = 0;
	vector<int> topoOrder;
	while (!q.empty()) {
		int u = q.front();
		q.pop();
		topoOrder.push_back(u);
		list<int>::iterator iter;
		for (iter = adj[u].begin(); iter != adj[u].end(); ++iter) {
			if (--in_degree[*iter] == 0) {
				q.push(*iter);
			}
		}
		cnt++;
	}

	if (cnt != V) {
		cout << "There is a cycle in the graph" << endl;
		return;
	}

	for (int i = 0; i < topoOrder.size(); ++i) {
		cout << topoOrder[i] << " ";
	}
	cout << endl;
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