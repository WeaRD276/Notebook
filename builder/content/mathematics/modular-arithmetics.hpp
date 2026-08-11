const int MOD = 998244353;

int add(int a, int b)
{
	return a + b < MOD ? a + b : a + b - MOD;
}

void updAdd(int& a, int b)
{
	a += b;
	if (a >= MOD)
		a -= MOD;
}

int sub(int a, int b)
{
	return a - b >= 0 ? a - b : a - b + MOD;
}

void updSub(int& a, int b)
{
	a -= b;
	if (a < 0)
		a += MOD;
}

int mult(int a, int b)
{
	return (ll)a * b % MOD;
}

int binPow(int a, ll n)
{
	int res = 1;
	while (n)
	{
		if (n & 1)
			res = mult(res, a);
		a = mult(a, a);
		n >>= 1;
	}
	return res;
}

int inv[N], fact[N], ifact[N];

void init()
{
	inv[1] = 1;
	FOR(i, 2, N)
	{
		inv[i] = mult(MOD - MOD / i, inv[MOD % i]);
	}
	fact[0] = ifact[0] = 1;
	FOR(i, 1, N)
	{
		fact[i] = mult(fact[i - 1], i);
		ifact[i] = mult(ifact[i - 1], inv[i]);
	}
}

int C(int n, int k)
{
	if (k < 0 || k > n)
		return 0;
	return mult(fact[n], mult(ifact[n - k], ifact[k]));
}
