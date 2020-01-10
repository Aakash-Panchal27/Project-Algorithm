#include <bits/stdc++.h>
using namespace std;

// Disjoint Set Union Structure
class Dsu
{
    int size;
    int numberofcomponents;
    
    public:
    
    int *IDs;
    vector<int> sizes;
    
    // Constructor
    Dsu(int size)
    {
        numberofcomponents = size;
        IDs = new int[size+1];
        sizes.push_back(0);
        
        for(int i=1; i <= size; i++)
        {
            IDs[i] = i;
            sizes.push_back(1);
        }
    }
    
    // Find the ID of the component
    int find(int p)
    {
        int root = p;
        
        while(p != IDs[p])
            p = IDs[p];
        
        //path compression
        while(p != root)
        {
            int temp = root;
            root = IDs[temp];
            IDs[temp] = p;
        }
        
        return p;
    }
    
    
    // Join two components
    void unify(int a, int b)
    {
        int ida = find(a);
        int idb = find(b);
        
        if(ida == idb) return;
        
        //smaller will unify with bigger set
        if(sizes[ida] > sizes[idb])
        {
            IDs[idb] = IDs[ida];
            sizes[ida] += sizes[idb];
        }
        else
        {
            IDs[ida] = IDs[idb];
            sizes[idb] += sizes[ida];
        }
        
        numberofcomponents--;
    }
};

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
	
	int min_cost = 0;
	
	Dsu unionfind(no_vertices);
	
	for(int i = 0; i < no_edges; i++)
	{
		int ida = unionfind.find(graph[i].from);
		int idb = unionfind.find(graph[i].to);
		
		// Connecting two set of vertices
		if(ida != idb)
		{	
			unionfind.unify(ida,idb);
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
