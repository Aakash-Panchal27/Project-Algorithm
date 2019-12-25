#include <bits/stdc++.h>
using namespace std;
#define MAX_DIST 100000000


struct edge {
	int from, to, weight;
	
	edge(int a,int b,int w)
	{
		from = a;
		to = b;
		weight = w;
	}
	
};


int Shortest_Path(vector<vector<edge> > &graph, int source, int vertex,
								vector<int> &distances, vector<int> &parent)
{
	if(vertex == source)
		return 0;
	
	if(distances[vertex] != MAX_DIST)
		return distances[vertex];
	
	for(auto vedge: graph[vertex])
	{
		int new_distance = Shortest_Path(graph, source, vedge.from, 
										distances, parent) + vedge.weight;
		if(new_distance < distances[vertex])
		{
			distances[vertex] = new_distance;
			parent[vertex] = vedge.from;
		}
	}
	
	return distances[vertex];
	
}

void printpath(vector<int>& parent, int vertex, int source, int destination) 
{ 
	if(vertex == source)
	{
		cout << source << "-->";
		return;
	}
    printpath(parent, parent[vertex], source, destination);
    cout << vertex << (vertex==destination ? "\n" : "-->");
}


int main()
{
	
	int no_vertices = 6;
	
	vector<vector<edge> > graph(no_vertices+1, vector<edge>());
	
	// Making the graph using
	// Reverse edges
	graph[2].push_back(edge(1,2,1));
	graph[2].push_back(edge(1,2,6));
	graph[4].push_back(edge(2,4,1));
	graph[3].push_back(edge(4,3,1));
	graph[5].push_back(edge(3,5,1));
	graph[5].push_back(edge(2,5,7));
	graph[6].push_back(edge(4,6,3));
	
	
	vector<int> distances(no_vertices + 1, MAX_DIST), parent(no_vertices +1, -1);
	
	int source = 1, destination = 5;
	
	distances[source] = 0;
	
	for(int i = 1; i <= no_vertices; i++)
		if(distances[i] == MAX_DIST)
			Shortest_Path(graph, source, i, distances, parent);
			
	for(int i = 1; i <= no_vertices; i++)
		cout << distances[i] << " ";
	
	
	return 0;
}
