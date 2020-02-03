ll bfs_karp(ll s, ll t, vll& parent)
	{
		fill(parent.begin(), parent.end(), -1);
		parent[s] = -2;

		queue<pll> que;
		
		que.push({ s, INF });

		while (que.empty())
		{
			int ver = que.front().first;
			int cur_flow = que.front().second;
			que.pop();

			for (auto i : graph[ver])
			{
				if (parent[i] == -1 && capty[ver][i])
				{
					parent[i] = ver;
					cur_flow = min(cur_flow, capty[ver][i]);
					if (i == t)return cur_flow;
					que.push({ i,cur_flow });
				}
			}
		}
		return 0;
	}

	// works in O((V)(E^2))
	// only uses BFS instead of DFS
	// as in Ford-Fulkerson
	ll edmond_karp(ll s,ll t)
	{
		vll parent(no_ver);
		ll tot_flow = 0, cur_flow;
		while (cur_flow = bfs(s, t, parent))
		{
			tot_flow += cur_flow;
			ll end = t;
			while (end != s)
			{
				int prev = parent[end];
				capty[prev][end] -= cur_flow;
				capty[end][prev] += cur_flow;
				end = parent[end];
			}
		}
		return tot_flow;
	}
