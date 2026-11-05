struct PersSegTree
{
	int n, lg;
	vector<Node> t;
	VI L, R, roots;

	PersSegTree(unsigned int _n): PersSegTree(vector<Node>(_n)) {}
	PersSegTree(const vector<Node>& ar)
	{
		n = bit_ceil(ar.size());
		lg = __lg(n);
		t.assign(2 * n, Node());
		L = R = VI(2 * n);
		FOR (i, 0, sz(ar))
			t[i + n] = ar[i];
		RFOR (i, n, 1)
		{
			L[i] = i << 1;
			R[i] = (i << 1) | 1;
			t[i] = op(t[L[i]], t[R[i]]);
		}
		roots.pb(1);
	}
	int upd(int ver, int p, const Node& val)
	{
		int v = roots[ver];
		roots.pb(sz(t));
		RFOR (b, lg, 0)
		{
			int bit = (p >> b) & 1, nxt = sz(t) + 1;
			L.pb(bit ? L[v] : nxt);
			R.pb(bit ? nxt : R[v]);
			v = bit ? R[v] : L[v];
			t.pb(Node());
		}
		t.pb(val);
		L.pb(0);
		R.pb(0);
		RFOR (i, sz(t) - 1, roots.back())
			t[i] = op(t[L[i]], t[R[i]]);
		return sz(roots) - 1;
	}
	// [l, r)
	Node query(int ver, int l, int r)
	{
		Node res;
		vector<array<int, 3>> st = {{roots[ver], 0, n}};
		while (!st.empty())
		{
			auto [v, lo, hi] = st.back();
			st.pop_back();
			if (r <= lo || hi <= l)
				continue;
			if (l <= lo && hi <= r)
			{
				res = op(res, t[v]);
				continue;
			}
			int m = (lo + hi) >> 1;
			st.pb({R[v], m, hi});
			st.pb({L[v], lo, m});
		}
		return res;
	}
};
