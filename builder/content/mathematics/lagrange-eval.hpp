// Evaluates P(k), where P is at most degree n-1 polynomial with values P[0..n-1]
int lagrange_eval(const vector<int>& P, int k)
{
	if (k < 0)
		return 0;
	int n = sz(P);
	if (k < n)
		return P[k];

	vector<int> pref(n + 1), suf(n + 1);
	pref[0] = suf[n] = 1;
	FOR (i, 0, n)
	{
		pref[i + 1] = mult(pref[i], sub(k, i));
	}
	RFOR (i, n, 0)
	{
		suf[i] = mult(suf[i + 1], sub(k, i));
	}

	int res = 0;
	FOR (i, 0, n)
	{
		int num = mult(P[i], mult(pref[i], suf[i + 1]));
		int den = mult(ifact[i], ifact[n - 1 - i]);
		if ((n - 1 - i) & 1)
			den = sub(0, den); 
		res = add(res, mult(num, den));
	}
	return res;
}
