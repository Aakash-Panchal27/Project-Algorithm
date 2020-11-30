#include<bits/stdc++.h>
#define forr(i,z,u,l) for(i=z;i<u;i+=l)
#define f(i,n) for(i=0;i<n;i++)
using namespace std;
#define F first
#define S second
#define vi vector<int>
#define vll vector<long double>
#define vvi vector<vector<int>>
#define vvll vector<vector<long double>>
#define vs vector<string>
#define vb vector<bool>
#define all(v) v.begin(),v.end()
#define ump unordered_map
#define dbg(x) cout<<#x<<" : "<<x
using ll = long double;
#define pii pair<int,int>
#define pll pair<ll,ll>
#define vpll vector<pll>
#define vvpll vector<vector<pll>>
#define endl "\n"
const ll M = 1e9 + 7;
int n,m,i,j,k;


// Class that solves Transportation Problem

class TP
{
	private:
	
	vvll cost_matrix;
	vll supply,demand;
	vvpll processor;
	vector<vb> isE;
	ll E;
	
	public:
	
	TP(vvll& cm,vll& s, vll& d)
	{
	    cost_matrix.resize(n, vll(m));
	    cost_matrix = cm;
	    processor.resize(n,vpll(m,pll()));
	    f(i,n)f(j,m){
	        processor[i][j].F = cost_matrix[i][j];
	        processor[i][j].S = 0;
	    }
	    supply.resize(n);
	    demand.resize(m);
	    supply = s;
	    demand = d;
	    ll supply_sum = accumulate(all(supply),0ll);
	    ll demand_sum = accumulate(all(demand),0ll);
	   
	    // UNBALANCED CASE---*************************
	    if(supply_sum != demand_sum){
	        if(supply_sum > demand_sum){
	            f(i,n)processor[i].push_back({0,0}),cost_matrix[i].push_back(0);
	            demand.push_back(supply_sum - demand_sum);
	            m++;
	        }
	        else{
	            processor.push_back(vector<pair<ll,ll>>(m,{0,0}));
	            cost_matrix.push_back(vector<ll>(m,0));
	            n++;
	            supply.push_back(demand_sum - supply_sum);
	        }
	    }
	    
	    isE.resize(n,vb(m));
	    E = 1e-5;
	    
	}
	
	/*************************************************************/
	// VAM Method to find Initial Solution
	void VAM()
	{
	    vvll temp(cost_matrix);
	    vector<vector<bool>> active(n,vector<bool>(m,true));
	    vector<bool> colac(m,true),rowac(n,true);
	    vll tsupp = supply;
	    vll tdem = demand;
	    int deactivated = 0, aakash = 0;
	    while(deactivated < n*m) {
	        int aa = 0, bb = 0;
	        aakash = 0;
	        f(i,n){
	            f(j,m){
	                if(active[i][j]) {
	                    aakash++;
	                    aa = i;
	                    bb = j;
	                }
	            }
	        }
	        if(aakash == 1){
	            processor[aa][bb].S = tsupp[aa];
	            break;
	        }
    	    vll row_diff(n);
    	    vll col_diff(m);
            f(j,n){
                ll mn = LONG_MAX, mn2 = LONG_MAX;
                f(k,m){
                    if(active[j][k]) {
        	            if(temp[j][k] < mn){
        	                mn2 = mn;
        	                mn = temp[j][k];
        	            }
        	            else if(temp[j][k] < mn2){
        	                mn2 = temp[j][k];
        	            }
                    }
                }
                row_diff[j] = mn2 - mn;
            }
            f(j,m){
                ll mn = LONG_MAX, mn2 = LONG_MAX;
                f(k,n){
                    if(active[k][j]) {
        	            if(temp[k][j] < mn){
        	                mn2 = mn;
        	                mn = temp[k][j];
        	            }
        	            else if(temp[k][j] < mn2){
        	                mn2 = temp[k][j];
        	            }
                    }
                }
                col_diff[j] = mn2 - mn;
            }
            
            /*
            f(i,n)cout << row_diff[i] << " ";
            cout << endl;
            f(i,m)cout << col_diff[i] << " ";
            cout << endl;
            */
            
            ll col_max=0,col_id;
            f(i,m){
                if(colac[i] && col_diff[i] > col_max){
                    col_max = col_diff[i];
                    col_id = i;
                }
            }
            ll row_max = 0,row_id;
            f(i,n){
                if(rowac[i] && row_diff[i] > row_max){
                    row_max = row_diff[i];
                    row_id = i;
                }
            }
            if(col_max > row_max){
                ll mn = LONG_MAX;
                ll id = -1;
                f(i,n){
                    if(active[i][col_id] && temp[i][col_id] < mn) {
                        mn = temp[i][col_id];
                        id = i;
                    }
                }
                if(tsupp[id] > tdem[col_id]){
                    tsupp[id] -= tdem[col_id];
                    processor[id][col_id].S = tdem[col_id];
                    f(i,n){
                        if(active[i][col_id]){
                            active[i][col_id] = false;
                            deactivated++;
                        }
                    }
                    colac[col_id] = false;
                }
                else{
                    tdem[col_id] -= tsupp[id];
                    processor[id][col_id].S = tsupp[id];
                    f(i,m){
                        if(active[id][i]){
                            active[id][i] = false;
                            deactivated++;
                        }
                    }
                    rowac[id] = false;
                }
            }
            else{
                ll mn = LONG_MAX;
                ll id = -1;
                f(i,m){
                    if(active[row_id][i] && temp[row_id][i] < mn) {
                        mn = temp[row_id][i];
                        id = i;
                    }
                }
                if(tsupp[row_id] > tdem[id]){
                    tsupp[row_id] -= tdem[id];
                    processor[row_id][id].S = tdem[id];
                    f(i,n)active[i][id] = false;
                    f(i,n){
                        if(active[i][id]){
                            active[i][id] = false;
                            deactivated++;
                        }
                    }
                    colac[id] = false;
                }
                else{
                    tdem[id] -= tsupp[row_id];
                    processor[row_id][id].S = tsupp[row_id];
                    f(i,m){
                        if(active[row_id][i]) {
                            active[row_id][i] = false;
                            deactivated++;
                        }
                    }
                    rowac[row_id] = false;
                }
            }
        }
        cout << "Initial BFS: " << endl;
	    ll cost = 0;
	    f(i,n) {
	        f(j,m){
	            if(processor[i][j].S != 0) {
	                cost += processor[i][j].S * cost_matrix[i][j];
	                cout << "x" << i+1 << j+1 << " = " << processor[i][j].S << ", ";
	            }
	        }
	    }
	    cout << endl;
	    cout << "cost: " << cost << endl;
	}
	
	
	/*************************************************************/
	// LOOP Finder
	vector<pair<int,int>> loop_finder(map<pair<int,int>,vector<pair<int,int>>>& adjacency_list,
	                                map<pair<int,int>,bool> visited, pair<int,int> x,
	                                vector<pair<int,int>> loop)
    {
        visited[x] = 1;
        loop.push_back(x);
        if(loop.size() >= 3)
        {
            if((loop[loop.size()-1].F == loop[loop.size()-2].F
                && loop[loop.size()-2].F == loop[loop.size()-3].F)
            ||(loop[loop.size()-1].S == loop[loop.size()-2].S 
                && loop[loop.size()-2].S == loop[loop.size()-3].S))
                loop.erase(loop.begin()+loop.size()-2);
        }
        if(loop.size() >= 4)
        {
            if(loop[loop.size()-1].F == loop[0].F || 
                loop[loop.size()-1].S == loop[0].S)
             return loop;
        }
        for(auto y : adjacency_list[x])
        {
            if(!visited[y])
            {
                auto v = loop_finder(adjacency_list, visited, y, loop);
                if(v.size() > 0)
                    return v;
            }
        }
        vector<pair<int,int>> temp;
        return temp;
    }
	
	/*************************************************************/
	// MODI Method Code to find Optimal Solution
	// It also handles Degenerate CAses
	void MODI()
	{
	    while(true){
	        int needed = 0;
    	    f(i,n){
    	        f(j,m){
    	            if(processor[i][j].S != 0)
    	                needed++;
    	        }
    	    }
    	    if(needed < n + m - 1){
    	        int aa,bb;
    	        ll mn = LONG_MAX;
    	        f(i,n){
    	            f(j,m){
    	                if(processor[i][j].S == 0 && mn > processor[i][j].F){
    	                    mn = min(mn,processor[i][j].F);
    	                    aa = i;
    	                    bb = j;
    	                }
    	            }
    	        }
    	        processor[aa][bb].S = E;
    	    }
	        vll u(n),v(m);
	        vector<bool> ufound(n),vfound(m);
	        v[0] = 0;
	        vfound[0] = true;
	        while( any_of(all(ufound),[](bool check){return check==false;}) || 
	                any_of(all(vfound),[](bool check){return check==false;}) ) {
	            
	            f(i,n){
	                f(j,m){
	                    if(processor[i][j].S != 0) {
    	                    if(ufound[i] && !vfound[j]){
    	                        v[j] = processor[i][j].F - u[i];
    	                        vfound[j] = true;
    	                    }
    	                    else if(vfound[j] && !ufound[i]){
    	                        u[i] = processor[i][j].F - v[j];
    	                        ufound[i] = true;
    	                    }
	                    }
	                }
	            }
	        }
	        vvll delta(n,vll(m,0));
	        bool done = true;
	        f(i,n){
	            f(j,m){
	                if(processor[i][j].S == 0){
	                    delta[i][j] = processor[i][j].F - (u[i]+v[j]);
	                    if(delta[i][j] < 0){
	                        done = false;
	                    }
	                }
	            }
	        }
	        if(done) {
	            cout << "Optimal Solution: \n";
	            ll cost = 0;
        	    f(i,n) {
        	        f(j,m){
        	            if(processor[i][j].S != 0) {
        	                cost += processor[i][j].S * cost_matrix[i][j];
        	                cout << "x" << i+1 << j+1 << " = " << round(processor[i][j].S);
        	                if(!(i==n-1 && j==m-1))
        	                    cout << ", ";
        	            }
        	        }
        	    }
        	    cout << endl;
        	    cout << "Optimal cost: " << round(cost) << endl;
        	    break;
	        }
	        else{
	            ll mn = 0;
	            int bi,bj;
	            f(i,n){
	                f(j,m){
	                    if(mn > delta[i][j]){
	                        mn = delta[i][j];
	                        bi = i;
	                        bj = j;
	                    }
	                }
	            }
	            vector<pair<int,int>> loop;
                map<pair<int,int>,vector<pair<int,int>>> adjlist;
                f(i,n){
                    f(j,m){
                        if(processor[i][j].S != 0 || (i==bi && j==bj)){
                            f(k,n){
                                if((processor[k][j].S != 0 || (k==bi && j==bj)) && k!=i){
                                    adjlist[{i,j}].push_back({k,j});
                                }
                            }
                            f(k,m){
                                if((processor[i][k].S != 0 || (i==bi && k==bj)) && k!=j){
                                    adjlist[{i,j}].push_back({i,k});
                                }
                            }
                        }
                    }
                }
	            
                map<pair<int,int>,bool> visited;
                loop = loop_finder(adjlist,visited,pair<int,int>({bi,bj}),loop);
	            
	            mn = LONG_MAX;
	            bool even = false;
	            for(auto it : loop){
	                if(even && processor[it.F][it.S].S != 0)
	                    mn = min(mn,processor[it.F][it.S].S);
	                even = !even;
	            }
	            even = false;
	            for(auto it : loop){
	                if(even)
	                    processor[it.F][it.S].S -= mn;
	                else 
	                    processor[it.F][it.S].S += mn;
	                even = !even;
	            }
	        }
	    }
	}
};

signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>m;
	vvll cm(n,vll(m));
	f(i,n)
	    f(j,m)
	        cin>>cm[i][j];
	vll supply(n), demand(m);
	f(i,n)cin>>supply[i];
	f(i,m)cin>>demand[i];
	TP SolveTP(cm, supply, demand);
	SolveTP.VAM();
	SolveTP.MODI();
	return 0;
}
