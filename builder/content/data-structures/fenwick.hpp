// methods work in 0-indexing
struct Fenwick
{
	int n;
	VL t;
	
	Fenwick (int _n = 0): n(_n + 1), t(n) {}
	Fenwick (const VL& ar)
	{
		n = sz(ar) + 1;
		t.assign(n, 0);
		FOR (i, 1, n)
		{
			t[i] += ar[i - 1];
			int x = i + (i & -i);
			if (x < n)
				t[x] += t[i];
		}
	}
	void upd(int x, ll val)
	{
		x++;
		while (x < n)
		{
			t[x] += val;
			x += x & -x;
		}
	}
	ll getSum(int x)
	{
		ll res = 0;
		while (x)
		{
			res += t[x];
			x -= x & -x;
		}
		return res;
	}
	// [l, r]
	ll query(int l, int r)
	{
		return getSum(r + 1) - getSum(l);
	}
};
