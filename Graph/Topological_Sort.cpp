#include <bits/stdc++.h>
using namespace std;
#define MAX_DIST 100000000

void dfs(vector<vector<int> > &graph, int start, list<int> &linked_list, vector<bool>& visited)
{
	visited[start] = true;
	
	for(auto i: graph[start])
		if(!visited[i])
			dfs(graph, i, linked_list, visited);
	
	linked_list.push_front(start);
	
}

void Topological_sort(int no_vertices, vector<vector<int> > &graph)
{
	vector<bool> visited(no_vertices + 1);
	
	list<int> linked_list;
	
	for(int i = 1; i <= no_vertices; i++)
		if(!visited[i])
			dfs(graph, i, linked_list, visited);
	
	for(auto vertex: linked_list)
		cout << vertex << " ";
	
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
