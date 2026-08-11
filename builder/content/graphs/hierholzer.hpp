/**
 * Description: Finds an Eulerian path in a directed or undirected graph.
 * $g$ is a graph with $n$ vertices. $g[u]$ is a vector of pairs $(v, \text{edge\_id})$. $m$ is the number of edges in the graph.
 * The vertices are numbered from $0$ to $n - 1$, and the edges - from $0$ to $m - 1$.
 * If there is no Eulerian path, returns $\{\{-1\}, \{-1\}\}$.
 * Otherwise, returns the path in the form (vertices, edges) with vertices containing $m + 1$ elements and edges containing $m$ elements.
 * If you need an Eulerian cycle, check vertices[0] = vertices.back().
 */
// f14a40 for undirected
tuple<bool, int, int> checkDirected(vector<vector<pii>>& g)
{
	int n = sz(g), v1 = -1, v2 = -1;
	bool bad = false;
	VI degIn(n);
	FOR(u, 0, n)
		for (auto [v, e] : g[u])
			degIn[v]++;
	FOR(u, 0, n)
	{
		bad |= abs(degIn[u] - sz(g[u])) > 1;
		if (degIn[u] < sz(g[u]))
		{
			bad |= v2 != -1;
			v2 = u;
		}
		else if (degIn[u] > sz(g[u]))
		{
			bad |= v1 != -1;
			v1 = u;
		}
	}
	return {bad, v1, v2};
}

/*tuple<bool, int, int> checkUndirected(vector<vector<pii>>& g)
{
	int n = sz(g), v1 = -1, v2 = -1;
	bool bad = false;
	FOR(u, 0, n)
	{
		if (sz(g[u]) & 1)
		{
			bad |= v2 != -1;
			if (v1 == -1)
				v1 = u;
			else
				v2 = u;
		}
	}
	return {bad, v1, v2};
}*/

pair<VI, VI> hierholzer(vector<vector<pii>> g, int m)
{
	// checkUndirected if undirected
	auto [bad, v1, v2] = checkDirected(g);
	if (bad)
		return {{-1}, {-1}};
	if (v1 != -1)
	{
		g[v1].pb({v2, m});
		// uncomment if undirected
		//g[v2].PB({v1, m});
		m++;
	}
	deque<pii> d;
	VI used(m);
	int v = 0, k = 0;
	while (m > 0 && g[v].empty())
		v++;
	while (sz(d) < m)
	{		
		while (k < m)
		{
			while (!g[v].empty() && used[g[v].back().y])
				g[v].pop_back();
			if (!g[v].empty())
				break;
			d.push_front(d.back());
			d.pop_back();
			v = d.back().x;
			k++;
		}
		if (k == m)
			return {{-1}, {-1}};
		d.pb(g[v].back());
		used[g[v].back().y] = true;
		g[v].pop_back();
		v = d.back().x;
	}
	while (v1 != -1 && d.back().y != m - 1)
	{
		d.push_front(d.back());
		d.pop_back();
		v = d.back().x;
	}
	VI vertices = {v}, edges;
	for (auto [u, e] : d)
	{
		vertices.pb(u);
		edges.pb(e);
	}
	if (v1 != -1)
	{
		vertices.pop_back();
		edges.pop_back();
	}
	return {vertices, edges};
}
