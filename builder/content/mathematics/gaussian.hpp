/**
 * Description: Solves the system $A x = b$.
 * Returns $(v, w)$ such that every solution $x$ can be represented as
 * $v + c_1 w_1 + c_2 w_2 + \dots + c_k w_k$, where $v$ is arbitrary solution,
 * $c_i$ are scalars and $w$ is basis.
 * If there is no solution, returns an empty pair.
 * If the solution is unique, then $w$ is empty.
 * Time: O(n m \min (n, m))
 */
pair<VI, vector<VI>> solveLinearSystem(vector<VI> a, VI b)
{
	int n = sz(a), m = sz(a[0]);
	assert(sz(b) == n);
	FOR(i, 0, n)
	{
		assert(sz(a[i]) == m);
		a[i].pb(b[i]);
	}
	int p = 0;
	VI pivots;
	FOR(j, 0, m)
	{
		// with doubles, abs(a[p][j]) -> max
		if (a[p][j] == 0)
		{
			int l = -1;
			FOR(i, p, n)
				if (a[i][j] != 0)
					l = i;
			if (l == -1)
				continue;
			swap(a[p], a[l]);
		}
		int in = binPow(a[p][j], MOD - 2);
		FOR(i, p + 1, n)
		{
			int c = mult(a[i][j], in);
			FOR(k, j, m + 1)
				updSub(a[i][k], mult(c, a[p][k]));
		}
		pivots.pb(j);
		p++;
		if (p == n)
			break;
	}
	FOR(i, p, n)
		if (a[i].back() != 0)
			return {};
	VI v(m);
	RFOR(i, p, 0)
	{
		int j = pivots[i];
		v[j] = a[i].back();
		FOR(k, j + 1, m)
			updSub(v[j], mult(a[i][k], v[k]));
		v[j] = mult(v[j], binPow(a[i][j], MOD - 2));
	}
	vector<VI> w;
	FOR(q, 0, m)
	{
		if (find(all(pivots), q) != pivots.end())
			continue;
		VI d(m);
		d[q] = 1;
		RFOR(i, p, 0)
		{
			int j = pivots[i];
			FOR(k, j + 1, m)
				updSub(d[j], mult(a[i][k], d[k]));
			d[j] = mult(d[j], binPow(a[i][j], MOD - 2));
		}
		w.pb(d);
	}
	return {v, w};
}
