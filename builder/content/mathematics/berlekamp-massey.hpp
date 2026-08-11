/**
 * Description: Finds a sequence of $d$ integers $c_1, \dots, c_d$
 * of the minimum length $d$ such that
 * $a_i = \sum_{j=1}^d c_j a_{i - j}$.
 */
VI berlekampMassey(const VI& a)
{
	VI c = {1}, bp = {1};
	int l = 0, b = 1, x = 1;
	FOR(j, 0, sz(a))
	{
		assert(sz(c) == l + 1);
		int d = a[j];
		FOR(i, 1, l + 1)
			updAdd(d, mult(c[i], a[j - i]));
		if (d == 0)
		{
			x++;
			continue;
		}
		VI t = c;
		int coef = mult(d, binPow(b, MOD - 2));
		if (sz(bp) + x > sz(c))
			c.resize(sz(bp) + x);
		FOR(i, 0, sz(bp))
			updSub(c[i + x], mult(coef, bp[i]));
		if (2 * l > j)
		{
			x++;
			continue;
		}
		l = j + 1 - l;
		bp = t;
		b = d;
		x = 1;
	}
	c.erase(c.begin());
	for (int& ci : c)
		ci = mult(ci, MOD - 1);
	return c;
}
