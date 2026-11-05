/**
 * Description: Lazy segment tree. \texttt{Node()} and \texttt{Tag()} must be identities.
 * \texttt{act(v, tg)} returns node \texttt{v} with \texttt{tg} applied,
 * \texttt{compose(a, b)} returns the tag "first \texttt{a}, then \texttt{b}".
 * Time: O(\log n)
 */
struct Node
{

};

struct Tag
{

};

Node op(const Node& l, const Node& r)
{

}

Node act(const Node& v, const Tag& tg)
{

}

Tag compose(const Tag& a, const Tag& b)
{

}

struct LazySegTree
{
	int n, lg;
	vector<Node> t;
	vector<Tag> lz;

	LazySegTree(unsigned int _n)
	{
		n = bit_ceil(_n);
		lg = __lg(n);
		t.assign(2 * n, Node());
		lz.assign(n, Tag());
	}
	LazySegTree(const vector<Node>& ar): LazySegTree(sz(ar))
	{
		FOR (i, 0, sz(ar))
			t[i + n] = ar[i];
		RFOR (i, n, 1)
			update(i);
	}
	void update(int v)
	{
		t[v] = act(op(t[v << 1], t[(v << 1) | 1]), lz[v]);
	}
	void apply(int v, const Tag& tg)
	{
		t[v] = act(t[v], tg);
		if (v < n)
			lz[v] = compose(lz[v], tg);
	}
	void push(int v)
	{
		apply(v << 1, lz[v]);
		apply((v << 1) | 1, lz[v]);
		lz[v] = Tag();
	}

	void set(int p, Node val)
	{
		p += n;
		RFOR (i, lg + 1, 1)
			push(p >> i);
		t[p] = val;
		FOR (i, 1, lg + 1)
			update(p >> i);
	}
	Node get(int p)
	{
		p += n;
		RFOR (i, lg + 1, 1)
			push(p >> i);
		return t[p];
	}
	// [l, r)
	void upd(int l, int r, const Tag& tg)
	{
		if (l == r)
			return;
		l += n;
		r += n;
		RFOR (i, lg + 1, 1)
		{
			push(l >> i);
			push((r - 1) >> i);
		}
		for (int a = l, b = r; a < b; a >>= 1, b >>= 1)
		{
			if (a & 1) apply(a++, tg);
			if (b & 1) apply(--b, tg);
		}
		FOR (i, 1, lg + 1)
		{
			update(l >> i);
			update((r - 1) >> i);
		}
	}
	// [l, r)
	Node query(int l, int r)
	{
		if (l == r)
			return Node();
		l += n;
		r += n;
		RFOR (i, lg + 1, 1)
		{
			push(l >> i);
			push((r - 1) >> i);
		}

		Node resL, resR;
		while (l < r)
		{
			if (l & 1) resL = op(resL, t[l++]);
			if (r & 1) resR = op(t[--r], resR);
			l >>= 1;
			r >>= 1;
		}
		return op(resL, resR);
	}
};
