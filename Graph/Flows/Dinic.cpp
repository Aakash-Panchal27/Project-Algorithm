ll INF 1e18

struct edge {
    ll v, u;
    long long cap, flow = 0;
    edge(ll v, ll u, long long cap) : v(v), u(u), cap(cap) {}
};


struct Dinic {
    vector<edge> edges;
    vector<vector<ll>> adj;
    ll n, idno
    ll s, t;
    vector<ll> level, ptr;
    queue<ll> q;

    Dinic(ll n, ll s, ll t) : n(n), s(s), t(t) 
    {
        adj.resize(n);
        level.resize(n);
        ptr.resize(n);
    }

    void add_edge(ll v, ll u, ll cap) 
    {
        edges.emplace_back(v, u, cap);
        edges.emplace_back(u, v, 0);
        adj[v].push_back(idno);
        adj[u].push_back(idno + 1);
        idno += 2;
    }

	// create the level graph
    bool bfs() {
        while (!q.empty()) 
        {
            ll v = q.front();
            q.pop();
            for (ll id : adj[v]) 
            {
                if (edges[id].cap - edges[id].flow < 1)
                    continue;
                if (level[edges[id].u] != -1)
                    continue;
                level[edges[id].u] = level[v] + 1;
                q.push(edges[id].u);
            }
        }
        return level[t] != -1;
    }

	// flow cross the level graph
	// using dfs as usual in Karp
	// considering the blocking flow
    ll dfs(ll v, ll pushed) 
    {
        if (pushed == 0)
            return 0;
        if (v == t)
            return pushed;
        for (ll& cid = ptr[v]; cid < (ll)adj[v].size(); cid++) 
        {
            ll id = adj[v][cid];
            ll u = edges[id].u;
            if (level[v] + 1 != level[u] || edges[id].cap - edges[id].flow < 1)
                continue;
            
            ll tr = dfs(u, min(pushed, edges[id].cap - edges[id].flow));
            
            if (tr == 0)
                continue;
            
            // after finding the path update the new flows
            edges[id].flow += tr;
            edges[id + 1].flow -= tr;
            
            return tr;
        }
        return 0;
    }

    ll flow() {
        ll tot_flow = 0;
        while (true) 
        {
            fill(level.begin(), level.end(), -1);
            level[s] = 0;
            q.push(s);
            
            if (!bfs())
                return tot_flow;
            
            fill(ptr.begin(), ptr.end(), 0ll);
            
            while (ll pushed = dfs(s, INF)) 
            {
                tot_flow += pushed;
            }
        }
        return tot_flow;
    }
};
