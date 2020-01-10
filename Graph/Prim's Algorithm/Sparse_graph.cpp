#include <bits/stdc++.h>
#define MAX_Weight 1000000000
using namespace std;

int main() 
{
	int no_vertices = 4;
	
	vector<vector<pair<int,int>> > graph(no_vertices+1, vector<pair<int,int>>());
	
	graph[1].push_back({2,6});	// A-B
	graph[2].push_back({1,6});
	graph[1].push_back({4,5});	// A-D
	graph[4].push_back({1,5});
	graph[2].push_back({3,3});	// B-C
	graph[3].push_back({2,3});
	graph[2].push_back({4,4});	// B-D
	graph[4].push_back({2,4});
	graph[3].push_back({4,2});	// C-D
	graph[4].push_back({3,2});
	
	// To track if the vertex is added in MST
	vector<bool> inMST(no_vertices+1);
	
	vector<int> minWeight(no_vertices+1, MAX_Weight);
	
	// Minimum finding(logN) DS
	set<pair<int,int>> Explored_edges;
	
	Explored_edges.insert({0,1});
	
	for(int i=2;i<no_vertices+1;i++)
	{
		Explored_edges.insert({MAX_Weight,i});
	}
	
	int VertinMST = 0, MSTcost = 0;
	
	minWeight[1] = 0;
	
	while(VertinMST < no_vertices)
	{
		if(Explored_edges.empty())
		{
			cout << "There is no MST" << endl;
			break;
		}
		
		// vertex connected by Minimum weighted edge
		int vertex = Explored_edges.begin()->second;
		
		MSTcost += minWeight[vertex];
		
		inMST[vertex] = true;
		VertinMST++;
		
		Explored_edges.erase(Explored_edges.begin());
		
		// Exploring the adjacent edges
		for(auto i:graph[vertex])
		{
			// If we reach by lesser weighted edge then update
			if(!inMST[i.first] && minWeight[i.first] > i.second)
			{
				// Previous more weighted edge
				Explored_edges.erase({minWeight[i.first],i.first});
				
				minWeight[i.first] = i.second;
				
				// New min. weighted edge
				Explored_edges.insert({minWeight[i.first],i.first});
			}
		}
		
	}
	
	cout << MSTcost << endl;
	
	return 0;
}
