#include <bits/stdc++.h>
using namespace std;
#define MAX_DIST 100000000


void Floyd_Warshall_with_NC(int no_vertices, vector<vector<int> > & distances)
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
				}
			}
		}
	}
	
	bool is_negative_cycle = false;
	
	// Check for negative cycle
	for (int i = 1; i <= no_vertices; ++i) 
	{
	    for (int a = 1; a <= no_vertices; ++a) 
	    {
	        for (int b = 1; b <= no_vertices; ++b) 
	        {
	        	// If there is a negative cycle, then update the distance to -Infinity
	            if (distances[a][i] < MAX_DIST && distances[i][i] < 0
	            						&& distances[i][b] < MAX_DIST)
	            {
	            	distances[a][b] = -MAX_DIST;
	            	is_negative_cycle = true;
	            }
	        }
	    }
	}
	
	if(is_negative_cycle)
	{
		cout << "The following pairs are affected by the negative cycle:" << endl;
		for (int a = 1; a <= no_vertices; ++a)
		{
		    for (int b = 1; b <= no_vertices; ++b)
		    {
		        if (distances[a][b] = -MAX_DIST)
		        {
		        	cout << a << "--" << b << endl;
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
	
	
	// Adding the edges virtually by
	// updating distance matrix
	distances[1][2]=1;
	distances[1][3]=-3;
	distances[2][4]=2;
	distances[4][1]=1;
	distances[3][4]=-2;
	
	for(int i = 1; i <= no_vertices; i++)
	{
		distances[i][i] = 0;
	}
	
	Floyd_Warshall_with_NC(no_vertices, distances);
	
	return 0;
}
