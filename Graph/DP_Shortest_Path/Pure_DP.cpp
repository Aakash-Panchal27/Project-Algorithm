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


// Kahn's Algorithm for Topological Sort
list<int> Topological_Sort(vector<vector<edge> > &graph, int no_vertices)
{
	list<int> topological_order;
	
	vector<int> indegrees(no_vertices + 1);
	
	for(int i = 1; i <= graph.size(); i++)
		for(int j = 0; j < graph[j].size(); j++)
			indegrees[graph[i][j].to]++;
	
	
	queue<int> que;
	
	for(int i = 1; i <= no_vertices; i++)
		if(indegrees[i] == 0)
			que.push(i);
	
	
	while(!que.empty())
	{
		int V = que.front();
		que.pop();
		
		topological_order.push_back(V);
		
		for(auto i: graph[V])
		{
			--indegrees[i.to];
			if(indegrees[i.to] == 0)
				que.push(i.to);
		}
	}
	
	return topological_order;
	
}

void shortest_path(vector<vector<edge> > &graph, vector<int> &distances, int source)
{
	distances[source] = 0;
	
	list<int> topological_order = Topological_Sort(graph, no_vertices);
	
	for(auto i: topological_order)
		for(auto edgev: graph[i])
			if(distances[edgev.to] > distances[edgev.from] + edgev.weight)
				distances[edgev.to] = distances[edgev.from] + edgev.weight;
}

int main()
{
	
	int no_vertices = 6;
	
	vector<vector<edge> > graph(no_vertices+1, vector<edge>());
	
	graph[1].push_back(edge(1,2,1));
	graph[1].push_back(edge(1,3,6));
	graph[2].push_back(edge(2,4,1));
	graph[4].push_back(edge(4,3,1));
	graph[3].push_back(edge(3,5,1));
	graph[2].push_back(edge(2,5,7));
	graph[4].push_back(edge(4,6,3));
		
	vector<int> distances(no_vertices + 1, MAX_DIST);
	
	int source = 1;
	
	shortest_path(graph, distances, source);
	
	for(int i = 1; i <= no_vertices; i++)
		cout << distances[i] << " ";
	
	return 0;
}
