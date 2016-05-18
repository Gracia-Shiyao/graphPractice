#pragma once
/*Interface of union-find structure*/
class DisjointSets {
	int * parent, *rnk;
	int n;
public:
	//constructor
	DisjointSets(int n);
	int find(int u);
	void merge(int u, int v);

};