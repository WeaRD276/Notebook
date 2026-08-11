struct Node
{
	
};

Node op(const Node& l, const Node& r)
{
	
}

struct SegTree
{
	int n;
	vector<Node> t;
	
	SegTree(unsigned int _n)
	{
		n = bit_ceil(_n);
		t.assign(2 * n, Node());
	}
	SegTree(const vector<Node>& ar)
	{
		n = bit_ceil(ar.size());
		t.assign(2 * n, Node());
		FOR (i, 0, sz(ar))
			t[i + n] = ar[i];
		
		RFOR (i, n, 1)
			t[i] = op(t[i << 1], t[(i << 1) | 1]);
	}
	void upd(int p, Node val)
	{
		p += n;
		t[p] = val;
		while (p >>= 1)
		{
			t[p] = op(t[p << 1], t[(p << 1) | 1]);
		}
	}
	// [l, r)
	Node query(int l, int r)
	{
		l += n;
		r += n;
		
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

