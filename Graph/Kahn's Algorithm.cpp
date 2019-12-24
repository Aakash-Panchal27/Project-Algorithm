#include <bits/stdc++.h>
using namespace std;
#define MAX_DIST 100000000


void Topological_sort(int no_vertices, vector<vector<int> > &graph)
{
	list<int> topological_order;
	
	vector<int> indegrees(no_vertices + 1);
	
	for(int i = 1; i <= graph.size(); i++)
		for(int j = 0; j < graph[j].size(); j++)
			indegrees[graph[i][j]]++;
	
	
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
			--indegrees[i];
			if(indegrees[i] == 0)
				que.push(i);
		}
		
	}
	
	for(auto i: topological_order)
		cout << i << " ";
	
}

int main()
{
	
	int no_vertices = 5;
	
	vector<vector<int> > graph(no_vertices+1, vector<int>());
	
	graph[1].push_back(3);
	graph[2].push_back(3);
	graph[3].push_back(4);
	graph[3].push_back(5);
	
	Topological_sort(no_vertices, graph);
	
	return 0;
}
