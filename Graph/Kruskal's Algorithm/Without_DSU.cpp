#include <bits/stdc++.h>
using namespace std;

// Object - Edge
struct edge{
	
	// Edge from -> to
	// having some weight
	int from, to, weight;
	
	edge(int a, int b, int w)
	{
		from = a;
		to = b;
		weight = w;
	}
	
};

bool comparator(edge& a, edge& b)
{
	return a.weight < b.weight;
}

signed main() {
	
	int no_vertices = 4, no_edges = 5;
	
	vector<edge> graph;
	
	// Edges of graph
	graph.push_back(edge(1,2,2));
	graph.push_back(edge(1,4,5));
	graph.push_back(edge(2,3,3));
	graph.push_back(edge(1,3,4));
	graph.push_back(edge(3,4,6));
	
	// sorting the edges
	sort(graph.begin(), graph.end(), comparator);
	
	// To remember the edges in ST
	vector<bool> is_in_ST(no_edges);
	
	// Array to maintain the IDs of 
	// vertices
	vector<int> ID(no_vertices+1);
	
	int min_cost = 0;
	
	for(int i = 0; i < no_vertices+1; i++)
		ID[i] = i;
	
	for(int i = 0; i < no_edges; i++)
	{
		int ida = ID[graph[i].from], idb = ID[graph[i].to];
		
		// Connecting two set of vertices
		if(ida != idb)
		{	
			for(int j=1; j<=no_vertices; j++)
				if(ID[j] == ida)
					ID[j] = idb;
			
			is_in_ST[i] = true;
			min_cost += graph[i].weight;
		}
		
	}
	
	// Cost to make MST
	cout << min_cost << endl;
	
	for(int i=0; i<no_edges; i++)
		if(is_in_ST[i])
			cout << graph[i].from << "---" << graph[i].to << endl;

	return 0;
}
