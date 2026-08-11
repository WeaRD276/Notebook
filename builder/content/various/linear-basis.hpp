const int MAX_BITS = 64;

struct LinearBasis
{
    bitset<MAX_BITS> basis[MAX_BITS];
    int size;

    LinearBasis()
    {
        size = 0;
    }

    void insert(bitset<MAX_BITS> x)
    {
        for (int i = MAX_BITS - 1; i >= 0; --i)
        {
            if (!x[i]) continue;
            if (basis[i].none())
            {
                basis[i] = x;
                ++size;
                return;
            }
            x ^= basis[i];
        }
    }

    bool canRepresent(bitset<MAX_BITS> x)
    {
		RFOR(i,MAX_BITS,0)
            if (x[i]) x ^= basis[i];
        return x.none();
    }

    bitset<MAX_BITS> getMaxXOR()
    {
        bitset<MAX_BITS> res;
		RFOR(i,MAX_BITS,0)
        {
			if ((res ^ basis[i]).to_ullong() > res.to_ullong())
                res ^= basis[i];
        }
        return res;
    }
};
