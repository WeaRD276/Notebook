/**
 * Description: Supporte everything related to seg trees
 */
template<class S, S (*op)(S, S), S (*e)(),
         class F, S (*mapping)(F, S),
         F (*composition)(F, F), F (*id)()>
struct LazySegTree
{
    int n, size, log;
    vector<S> t;
    vector<F> lz;

    LazySegTree(int _n = 0) : LazySegTree(vector<S>(_n, e())) {}
    LazySegTree(const vector<S>& v)
    {
        n = sz(v);
        size = 1;
        while (size < n) 
			size <<= 1;
        log = __builtin_ctz(size);
        t.assign(2 * size, e());
        lz.assign(size, id());
        FOR(i, 0, n) t[size + i] = v[i];
        RFOR(i, size, 1) update(i);
    }

    void update(int k) { t[k] = op(t[k << 1], t[k << 1 | 1]); }

    void all_apply(int k, F f)
    {
        t[k] = mapping(f, t[k]);
        if (k < size) lz[k] = composition(f, lz[k]);
    }

    void push(int k)
    {
        all_apply(k << 1, lz[k]);
        all_apply(k << 1 | 1, lz[k]);
        lz[k] = id();
    }

    void set(int p, S x)
    {
        p += size;
        RFOR(i, log + 1, 1) push(p >> i);
        t[p] = x;
        FOR (i, 1, log + 1) update(p >> i);
    }

    S get(int p)
    {
        p += size;
        RFOR(i, log + 1, 1) push(p >> i);
        return t[p];
    }

    // [l, r)
    S prod(int l, int r)
    {
        if (l == r) return e();
        l += size; r += size;
        RFOR(i, log + 1, 1)
        {
            if (((l >> i) << i) != l) push(l >> i);
            if (((r >> i) << i) != r) push((r - 1) >> i);
        }
        S sml = e(), smr = e();
        while (l < r)
        {
            if (l & 1) sml = op(sml, t[l++]);
            if (r & 1) smr = op(t[--r], smr);
            l >>= 1; r >>= 1;
        }
        return op(sml, smr);
    }

    S all_prod() { return t[1]; }

    void apply(int p, F f)
    {
        p += size;
        RFOR(i, log + 1, 1) push(p >> i);
        t[p] = mapping(f, t[p]);
        FOR(i, 1, log + 1) update(p >> i);
    }

    void apply(int l, int r, F f)
    {
        if (l == r) return;
        l += size; r += size;
        RFOR(i, log + 1, 1)
        {
            if (((l >> i) << i) != l) push(l >> i);
            if (((r >> i) << i) != r) push((r - 1) >> i);
        }
        int l2 = l, r2 = r;
        while (l < r)
        {
            if (l & 1) all_apply(l++, f);
            if (r & 1) all_apply(--r, f);
            l >>= 1; r >>= 1;
        }
        FOR (i, 1, log + 1)
        {
            if (((l2 >> i) << i) != l2) update(l2 >> i);
            if (((r2 >> i) << i) != r2) update((r2 - 1) >> i);
        }
    }
};
