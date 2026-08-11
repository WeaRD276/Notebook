struct Node
{
	int sm;
	Node* l; 
	Node* r;
	
	Node(int v = 0): sm(v), l(nullptr), r(nullptr) {}
	Node(Node* _l, Node* _r): sm(_l->sm + _r->sm), l(_l), r(_r) {}
};

struct PersSegTree
{
	int n;
	vector<Node*> t;
	
	PersSegTree(int _n)
	{
		n = _n;
		t.pb(build(0, n - 1));
	}
	Node* build(int l, int r)
	{
		if (l == r)
			return new Node();
		int m = (l + r) >> 1;
		return new Node(build(l, m), build(m + 1, r));
	}
	Node* upd(Node* v, int l, int r, int pos, int val)
	{
		if (l == r)
			return new Node(val);
		int m = (l + r) >> 1;
		if (pos <= m)
			return new Node(upd(v->l, l, m, pos, val), v->r);
		else
			return new Node(v->l, upd(v->r, m + 1, r, pos, val));
	}
	Node query(Node* v, int l, int r, int ql, int qr)
	{
		if (ql > r || qr < l)
			return Node();
		if (ql <= l && r <= qr) 
			return *v;
		int m = (l + r) >> 1;
		Node L = query(v->l, l, m, ql, qr);
		Node R = query(v->r, m + 1, r, ql, qr);
		return Node(&L, &R);
	}
	
	int upd(int ver, int pos, int val)
	{
		Node* nd = upd(t[ver], 0, n - 1, pos, val);
		t.pb(nd);
		return sz(t) - 1;
	}
	// [l, r]
	Node query(int ver, int l, int r)
	{
		return query(t[ver], 0, n - 1, l, r);
	}
};
