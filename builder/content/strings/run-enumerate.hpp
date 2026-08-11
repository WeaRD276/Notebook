/**
 * Description: Enumerate all tuples $(t, l, r)$ with $t$ being the minimum period of $s[l, r)$ and $r - l \ge 2 \cdot t$. 
 * $l$ and $r$ are maximal. In other words $(t, l - 1, r)$ and $(t, l, r + 1)$ do not satisfy the previous condition.
 * 
 * The number of runs is $\le |s|$. Other properties are stated at the end of the function.
 * Time: $O(n \log n)$, where $n = |s|$.
 */
struct Run
{
	int t, l, r;
	bool operator<(const Run& p) const
	{
		return make_tuple(t, l, r) < make_tuple(p.t, p.l, p.r);
	}
	bool operator==(const Run& p) const
	{
		return !(*this < p) && !(p < *this);
	}
};
vector<Run> runEnumerate(VI s) 
{
	int n = sz(s);
	LCP lcp(s); reverse(all(s));
	LCP rev(s); reverse(all(s));
	
	vector<Run> runs;
	FOR(inv, 0, 2)
	{
		VI st = {n};
		auto pop = [&](int i)
		{
			int j = st.back();
			int dist = j - i;
			int distPrev = st[sz(st) - 2] - j;
			int distMn = min(dist, distPrev);
			
			int len = lcp.queryLcp(i, j);
			if((len >= distMn && dist < distPrev) || 
				(len < distMn && ((s[i + len] < s[j + len]) ^ inv)))
				return true;
			return false;
		};
		
		RFOR(i, n, 0)
		{
			while(sz(st) > 1 && pop(i))
				st.pop_back();
			int j = st.back();
			int dist = j - i;
			st.pb(i);
			
			int x = rev.queryLcp(n - i, n - j);
			int y = lcp.queryLcp(i, j);
			if(x < dist && x + y >= dist) 
				runs.pb({dist, i - x, j + y});
		}
	}
	sort(all(runs));
	runs.resize(unique(all(runs)) - runs.begin());
	
	//ll sumLen = 0, sumCnt = 0, sum = 0;
	//for(auto [len, l, r] : runs)
	//	sumLen += len, sumCnt += (r - l) / len, sum += r - l;
	//assert(sz(runs) <= sz(s));
	//assert(sumLen <= LOG * sz(s));
	//assert(sumCnt <= 2 * sz(s));
	//assert(sum <= 2 * LOG * sz(s));
    return runs;
}
