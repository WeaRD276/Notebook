// returns first index p such that sum on [0, p] >= val or n if not found
int lower_bound(ll val)
{
	ll sm = 0;
	int pos = 0;
	for (int i = 1 << (31 - __builtin_clz(n)); i; i >>= 1)
	{
		if (pos + i < n && sm + t[pos + i] < val)
		{
			sm += t[pos + i];
			pos += i;
		}
	}
	return pos;
}
