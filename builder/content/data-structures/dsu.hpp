struct DSU
{
	int n;
	VI par, siz;
	
	DSU (int _n = 0)
	{
		n = _n;
		par.resize(n);
		iota(all(par), 0);
		siz.assign(n, 1);
	}
	int find(int v)
	{
		if (v == par[v])
			return v;
		return par[v] = find(par[v]);
	}
	bool unite(int a, int b)
	{
		a = find(a);
		b = find(b);
		if (a != b)
		{
			if (siz[a] < siz[b])
				swap(a, b);
			par[b] = a;
			siz[a] += siz[b];
			return true;
		}
		return false;
	}
};
