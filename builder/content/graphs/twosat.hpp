// ! remove adj_cond from scc 
struct TwoSat 
{
    int n, N;
    vector<VI> g;
    vector<VI> comps;
    vector<bool> val;

    TwoSat(int _n) : n(_n), N(2 * n), g(N), val(n, false) {}

	// add clause (x_a OR x_b). na, nb - whether to negate
    void add(int a, bool na, int b, bool nb) 
    {
        int A = 2 * a ^ na;
        int B = 2 * b ^ nb;
        int NA = A ^ 1;
        int NB = B ^ 1;
        g[NA].pb(B);
        g[NB].pb(A);
    }
	
	// returns true if the formula is satisfiable. in this case, val contains a valid assignment
    bool solve() 
    {
        comps.clear();
        scc(g, comps);

        VI id(N, -1);
        FOR (i, 0, sz(comps))
            for (int v : comps[i])
                id[v] = i;

        FOR (i, 0, n)
            if (id[2 * i] == id[2 * i + 1])
                return false;

        val.assign(n, false);
        FOR (i, 0, n)
            val[i] = (id[2 * i] > id[2 * i + 1]);

        return true;
    }
};
