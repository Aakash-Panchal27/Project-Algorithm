#include <bits/stdc++.h>
using namespace std;
#define MAX_DIST 100000000


void Floyd_Warshall(int no_vertices, vector<vector<int> > & distances, vector<vector<int> > & next)
{
	// i shows the phase
	for(int i = 1; i <= no_vertices; i++)
	{
		// Update distance matrix for all pairs
		for(int a = 1; a <= no_vertices; a++)
		{
			for(int b = 1; b <= no_vertices; b++)
			{
				
				if( distances[a][b] > distances[a][i]+distances[i][b] && 
				distances[a][i] < MAX_DIST && distances[i][b] < MAX_DIST )
				{
					distances[a][b]	= distances[a][i]+distances[i][b];
					
					// updating next vertex as a->i->b
					next[a][b] = next[a][i];
				}
			}
		}
	}
}


int main()
{
	
	int no_vertices=5;
	
	// N*N array to store the distances between every pair
	vector<vector<int> > distances(no_vertices+1, vector<int> (no_vertices+1, MAX_DIST));
	
	
	// N*N array to store the next vertex for every pair
	vector<vector<int> > next(no_vertices+1, vector<int> (no_vertices+1, -1));
	
	
	// Adding the edges virtually by
	// updating distance matrix and
	// next vertex matrix
	distances[1][2]=1, next[1][2] = 2;
	distances[1][3]=-3, next[1][3] = 3;
	distances[2][4]=2, next[2][4] = 4;
	distances[2][5]=1, next[2][5] = 5;
	distances[3][4]=-1, next[3][4] = 4;
	distances[3][5]=2, next[3][5] = 5;
	distances[4][5]=1, next[4][5] = 5;
	
	// Update all the diagonal elements
	for(int i = 1; i <= no_vertices; i++)
	{
		distances[i][i] = 0;
		next[i][i] = i;
	}
	
	Floyd_Warshall(no_vertices, distances, next);
	
	// Example of path reconstruction
	int source = 1, destination = 5;
	
	while(source != destination)
	{
		cout << source << " "; 
		source = next[source][destination];
	}
	
	cout << destination << endl;
	
	return 0;
}
