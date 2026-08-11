/**
 * Description: Cast your string to vector.
 * Don't forget about delimiters.
 * No need to add anything at the end.
 * $\text{sa}$ represents permutations of positions if you sort all suffixes.
 * Time: O(n \log n)
 */

void countSort(VI& p, const VI& c)
{
	int n = sz(p);
	VI cnt(n);
	FOR (i, 0, n)
		cnt[c[i]]++;
	VI pos(n);
	FOR (i, 1, n)
		pos[i] = pos[i - 1] + cnt[i - 1];
	VI p2(n);
	for (auto x : p)
	{
		int i = c[x];
		p2[pos[i]++] = x;
	}
	p = p2;
}

VI suffixArray(VI s)
{
	// strictly smaller than any other element
	s.pb(-1);
	int n = sz(s);
	VI p(n), c(n);
	iota(all(p), 0);
	sort(all(p), [&](int i, int j)
	{
		return s[i] < s[j];
	});
	int x = 0;
	c[p[0]] = 0;
	FOR (i, 1, n)
	{
		if (s[p[i]] != s[p[i - 1]])
			x++;
		c[p[i]] = x;
	}
	int k = 0;
	while ((1 << k) < n)
	{
		FOR (i, 0, n)
			p[i] = (p[i] - (1 << k) + n) % n;
		countSort(p, c);
		VI c2(n);
		pii pr = {c[p[0]], c[(p[0] + (1 << k)) % n]};
		FOR (i, 1, n)
		{
			pii nx = {c[p[i]], c[(p[i] + (1 << k)) % n]};
			c2[p[i]] = c2[p[i - 1]];
			if (pr != nx)
				c2[p[i]]++;
			pr = nx;
		}
		c = c2;
		k++;
	}
	p.erase(p.begin());
	return p;
}
