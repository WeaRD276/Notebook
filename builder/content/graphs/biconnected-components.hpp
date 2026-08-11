/**
 * Description: Colors the edges so that the vertices,
 * connected with the same color are still connected if you delete any vertex.
 * Time: $O(m)$
 **/

struct Graph
{
	int n, m;
	vector<pii> edges;
	vector<VI> g;

	VI used, par;
	VI tin, low, inComp;
	int t = 0, c = 0;
	VI st;

	// components of vertices
	// a vertex can be in several components
	vector<VI> verticesCol;
	// components of edges
	vector<VI> components;
	// col[i] - component of the i-th edge
	VI col;
	
	Graph(int _n = 0, int _m = 0): n(_n), m(_m), edges(m), g(n), 
	used(n), par(n, -1), tin(n), low(n), inComp(n), col(m, -1) {}
	
	void addEdge(int a, int b, int i)
	{
		assert(0 <= a && a < n);
		assert(0 <= b && b < n);
		assert(0 <= i && i < m);
		
		edges[i] = MP(a, b);
		g[a].pb(i);
		g[b].pb(i);
	}
	
	void addComp()
	{
		unordered_set<int> s;
		s.reserve(7 * sz(components[c]));
		for (auto e : components[c])
		{
			s.insert(edges[e].x);
			s.insert(edges[e].y);
			inComp[edges[e].x] = true;
			inComp[edges[e].y] = true;
		}
		verticesCol.pb(VI(all(s)));
	}

	void dfs(int v, int p = -1)
	{
		used[v] = 1;
		par[v] = p;
		low[v] = tin[v] = t++;
		int cnt = 0;
		for (auto e : g[v])
		{
			int to = edges[e].x;
			if (to == v)
				to = edges[e].y;
				
			if (p == to) continue;
			if (!used[to])
			{
				cnt++;
				st.pb(e);
				dfs(to, v);
				
				low[v] = min(low[v], low[to]);
				
				if ((par[v] == -1 && cnt > 1) || 
				(par[v] != -1 && low[to] >= tin[v]))
				{
					components.pb({});
					while (st.back() != e)
					{
						components[c].pb(st.back());
						col[st.back()] = c;
						
						st.pop_back();
					}
					components[c].pb(st.back());
					addComp();
					col[st.back()] = c++;
						
					st.pop_back();
				}
			}
			else
			{
				low[v] = min(low[v], tin[to]);
				if (tin[to] < tin[v])
					st.pb(e);
			}
		}	
	}
	void build()
	{			
		FOR (i, 0, n)
		{
			if (used[i]) continue;
			dfs(i, -1);
			if (st.empty()) continue;
			components.pb({});
			while (!st.empty())
			{
				int e = st.back();
				col[e] = c;
				components[c].pb(e);
				st.pop_back();
			}
			addComp();
			c++;
		}
		FOR (i, 0, n)
			if (!inComp[i])
				verticesCol.pb(VI(1, i));
	}
};
