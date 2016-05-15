#include <iostream>
#include <list>
#include <queue>
#include <stack>
#include <vector>
#include "Graph.h"
using namespace std;

class DirectGraph : protected Graph {
	
	void DFSUtil(int v, bool visited[]);
//	void topoSortUtil(int v, bool visited[], stack<int>& S);
	bool isCyclicUtil(int v, bool visited[], bool *rs);
public:
	DirectGraph(int v) :Graph(v) {
	};
	void addEdge(int v, int w);
	void DFS(int v); //start point of dfs
	void DFS();
	void BFS(int v); //start with vertex v
	void topologicalSort();
	bool isCyclic(); //return true if there is a cycle in this graph
};          

void DirectGraph::addEdge(int v, int w) {
	adj[v].push_back(w);
}

void DirectGraph::DFSUtil(int v, bool visited[]) {
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

void DirectGraph::DFS(int v) {
	bool *visited = new bool[V];
	for (int i = 0; i < V; ++i) {
		visited[i] = false;
	}
	DFSUtil(v, visited);
}

void DirectGraph::DFS() {
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

void DirectGraph::BFS(int s) {
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
void DirectGraph::topoSortUtil(int v, bool visited[], stack<int>& stk) {
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
void DirectGraph::topologicalSort() {
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
void DirectGraph::topologicalSort() {
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
bool DirectGraph::isCyclicUtil(int v, bool visited[], bool *rs) {
	if (visited[v] == false) {
		//mark the current node as visited and part of the recusion stack
		visited[v] = true;
		rs[v] = true;

		list<int>::iterator i;
		for (i = adj[v].begin(); i != adj[v].end(); ++i) {
			if (!visited[*i] && isCyclicUtil(*i, visited, rs))
				return true;
			else if (rs[*i]) {
				return true;
			}
		}
	}
	rs[v] = false;
	return false;
}
bool DirectGraph::isCyclic() {
	//mark all the vertices as not visited and not part of the recursion
	bool * visited = new bool[V];
	bool * recStack = new bool[V];

	for (int i = 0; i < V; ++i) {
		visited[i] = false;
		recStack[i] = false;
	}

	//Call the recursive helper function to detect cycle in different DFS trees
	for (int i = 0; i < V; ++i) {
		if (isCyclicUtil(i, visited, recStack)) {
			return true;
		}
	}
	return false;
}
/*
int main() {
	DirectGraph g{ 4 };
	g.addEdge(0, 1);
	g.addEdge(0, 2);
	g.addEdge(1, 2);
	g.addEdge(2, 0);
	g.addEdge(2, 3);
	g.addEdge(3, 3);

	cout << "\n DFS1:\n";
	g.DFS(2);
	cout << "\n DFS2:\n";
	g.DFS();
	cout << "\n BFS:\n";
	g.BFS(2);
	cout << "\n Topological Sort: \n";
	g.topologicalSort();
	
	bool isC = g.isCyclic();
	cout << "\n IsCyclic? \n";
	if (isC)
		cout << "Yes";
	else
		cout << "No";
}
*/