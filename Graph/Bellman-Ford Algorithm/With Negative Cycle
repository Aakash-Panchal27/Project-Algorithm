#include <bits/stdc++.h>
using namespace std;
#define MAX_DIST 100000000

// Function to print the required path 
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

// Function to print the required path 
void printcycle(vector<int>& parent, int vertex, int source, int destination) 
{ 
	if(vertex == source)
	{
		cout << source << "-->";
		return;
	}
    printcycle(parent, parent[vertex], source, destination);
    
    if(vertex == destination)
   		cout << vertex << "-->" << source << endl;
   	else
   		cout << vertex << "-->";
}

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

// Bellman-Ford Algorithm
bool Bellman_Ford(vector<edge> & edges, vector<int> & distance, vector<int> & parent)
{
	int no_vertices = 5;
	for (int i = 0; i < no_vertices - 1; i++)
	{
		// Loop over all the edges
		for(int j = 0; j < edges.size() ; j++)
		{
			if(distance[edges[j].from] != MAX_DIST) 
			{
				
				// Check for the Relaxation Condition
				if(distance[edges[j].to] > distance[edges[j].from] + edges[j].weight )
				{
					distance[edges[j].to] = distance[edges[j].from] + edges[j].weight;
					parent[edges[j].to] = edges[j].from; 
				}
			}
		}
	}
	
	bool is_negative_cycle = false;
	
	int last_relaxation = 0;
	
	// Running the outer loop one more time
	for(int j = 0; j < edges.size() ; j++)
	{
		// Check for the Relaxation Condition
		if(distance[edges[j].to] > distance[edges[j].from] + edges[j].weight )
		{
			distance[edges[j].to] = distance[edges[j].from] + edges[j].weight;
			parent[edges[j].to] = edges[j].from;
			last_relaxation = edges[j].to;
			is_negative_cycle = true;
		}
		
	}
	
	if(is_negative_cycle)
	{
		cout << "There is a negative cycle in the graph." << endl;
		return last_relaxation;
	}
	
	return 0;
}
	

int main()
{
	
	int no_vertices=5;
	
	// Array of edges
	vector<edge> edges;
	
	// Distance and Parent vertex storing arrays
	vector<int> distance(no_vertices+1, MAX_DIST), parent(no_vertices+1,-1);
	
	// Edges
	edges.push_back(edge(1,2,1));
	edges.push_back(edge(2,3,5));
	edges.push_back(edge(3,1,2));
	edges.push_back(edge(2,4,-10));
	edges.push_back(edge(4,3,4));
	edges.push_back(edge(3,5,1));
	
	// For the shake of example
	int source = 1, destination = 5;
	
	distance[1] = 0;
	
	int last_relaxation = Bellman_Ford(edges, distance, parent);
	
	if(!last_relaxation)
	{
		// Shortest distance from source to destination
		cout << distance[5] << endl;
		
		// Shortest path
		printpath(parent, 5, 1, 5);
	}
	else
	{
		int trapped = last_relaxation;
		
		// To find the negative_cycle, we can
		// use the last relaxation data
		// and loop back over parent vertices
		// for over no_vertices time, so that 
		// we get trapped in the negative cycle
		for(int i = 0; i < no_vertices; i++)
		{
			trapped = parent[trapped];
		}
		
		// Printing negative_cycle
		printcycle(parent, parent[trapped], trapped, parent[trapped]);
		
	}
	
	return 0;
}
