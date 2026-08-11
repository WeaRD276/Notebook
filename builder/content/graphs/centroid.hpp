VI g[N];
int siz[N];
bool usedC[N];

int dfsSZ(int v, int par)
{
	siz[v] = 1;
	for (auto to : g[v])
	{
		if (to != par && !usedC[to])
			siz[v] += dfsSZ(to, v);
	}
	return siz[v];
}

void build(int u)
{
	dfsSZ(u, -1);
	int szAll = siz[u];
	int pr = u;
	while (true)
	{
		int v = -1;
		for (auto to : g[u])
		{
			if (to == pr || usedC[to]) 
				continue;
			if (siz[to] * 2 > szAll)
			{
				v = to;
				break;
			}
		}
		if (v == -1)
			break;
		pr = u;
		u = v;
	}
	int cent = u;
	usedC[cent] = true;
	
	// here calculate f(cent)
		
	for (auto to : g[cent])
	{
		if (!usedC[to])
		{
			build(to);
		}
	}
}
