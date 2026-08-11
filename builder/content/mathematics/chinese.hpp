/**
 * Description: Code finds a specific structure of the answer.
 * Time: O(n^2) 
 */
ll chinese(VI m, VI p)
{
	int n = sz(m);
	FOR(i, 1, n)
	{
		ll a = 1;
		ll b = 0;
		RFOR(j, i, 0)
		{
			b = (b * p[j] + m[j]) % p[i];
			a = a * p[j] % p[i];
		}
		b = (m[i] - b + p[i]) % p[i];
		
		int c = p[i];
		auto [d, x, y] = gcdExt(a, c);
		
		if(b % d != 0)
			return -1;
		a /= d;
		b /= d;
		c /= d;
		
		b = (b * x % c + c) % c;
		m[i] = b;
		p[i] = c;
	}
	//specific structure where gcd(pi, pj) = 1
	ll res = m[n - 1];
	RFOR(i, n - 1, 0)
		res = res * p[i] + m[i];
	return res;
}
