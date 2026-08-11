/**
 * Description: $x \% p_i = m_i, \text{lcm}(p_i) \le 10^{18}, 0 \le x < \text{lcm}(p_i)$
 * $\rightarrow x$ or -1.
 * Time: O(n\log(\text{lcm}(p_i)))
 */
ll fastChinese(vector<ll> m, vector<ll> p)
{
	assert(sz(m) == sz(p));
	ll aa = p[0];
	ll bb = m[0];
	FOR(i, 1, sz(m))
	{
		ll b = (m[i] - bb % p[i] + p[i]) % p[i];
		ll a = aa % p[i];
		ll c = p[i];
		
		auto [d, x, y] = gcdExt(a, c);
		if(b % d != 0)
			return -1;
		a /= d;
		b /= d;
		c /= d;
		b = (b * (__int128)x % c + c) % c;
		
		bb = aa * b + bb;
		aa = aa * c;
	}
	return bb;
}
