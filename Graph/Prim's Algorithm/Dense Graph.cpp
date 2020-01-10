#include <bits/stdc++.h>
#define MAX_Weight 1000000000
using namespace std;

int main() 
{
	int no_vertices = 4;
	
	int graph[no_vertices+1][no_vertices+1];
	
	graph[1][2]=6;	// A-B
	graph[2][1]=6;
	graph[1][4]=5;	// A-D
	graph[4][1]=5;
	graph[2][3]=3;	// B-C
	graph[3][2]=3;
	graph[2][4]=4;	// B-D
	graph[4][2]=4;
	graph[3][4]=2;	// C-D
	graph[4][3]=2;
	
	// To track if the vertex is added in MST
	vector<bool> inMST(no_vertices + 1);
	
	int VertinMST = 0, MSTcost = 0;
	
	vector<int> minWeight(no_vertices + 1, MAX_Weight);
	minWeight[1] = 0;
	
	for(int i=1; i<=no_vertices; i++)
	{
		int minvertex = 0, weight = MAX_Weight;
		
		// Find the minimum weighted edge
		for(int j=1; j<=no_vertices; j++)
		{
			if(!inMST[j] && (minvertex==0 || minWeight[j] < minWeight[minvertex]))
			{
				minvertex = j;
				weight = minWeight[j];
			}
		}
		
		inMST[minvertex] = true;
		MSTcost += weight;
		
		// Update the min weights
		for(int j=1;j<=no_vertices;j++)
		{
			if(!inMST[j] && graph[minvertex][j] < minWeight[j])
			{
				minWeight[j] = graph[minvertex][j];
			}
		}
		
	}
	
	cout << MSTcost << endl;
	
	return 0;
}
