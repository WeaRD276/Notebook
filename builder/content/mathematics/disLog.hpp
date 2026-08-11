// Returns minimum x for which (a ^ x) % MOD = b % MOD, a and MOD are coprime.
int disLog(int a, int b)
{
	int n = sqrt(MOD) + 1;
	
	int an = binPow(a, n);
	unordered_map<int, int> vals;
	for (int q = 0, cur = b; q <= n; ++q) 
	{
        vals[cur] = q;
        cur = mult(cur, a);
    }
    
    for (int p = 1, cur = 1; p <= n; ++p) 
    {
        cur = mult(cur, an);
        if (vals.count(cur)) 
        {
			return n * p - vals[cur];
        }
    }
    return -1;
}
