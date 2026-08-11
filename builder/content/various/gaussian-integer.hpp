/**
 * Description: $n = am + b, \frac{n}{m} = a, n \% m = b$.
 * use \_\_gcd instead of gcd.\\
 * \textbf{Facts}: Primes of the form $4n + 3$ are Gaussian primes.
 * Uniqueness of prime factorization.
 */
ll closest(ll u, ll d)
{
	if(d < 0)
		return closest(-u, -d);
	if(u < 0)
		return -closest(-u, d);
	return (2 * u + d) / (2 * d);
}
struct num : complex<ll>
{	
	num(ll a, ll b = 0) : complex(a, b) {}
	num(complex a) : complex(a) {}
	num operator/ (num x)
	{
		num prod = *this * conj(x);
		ll D = (x * conj(x)).real();
		
		ll m = closest(prod.real(), D);
		ll n = closest(prod.imag(), D);
	
		return num(m, n);
	}
	num operator% (num x)
	{
		return *this - x * (*this / x);
	}
	bool operator == (num b)
	{
		FOR(it, 0, 4)
		{
			if(real() == b.real() && imag() == b.imag())
				return true;
			b = b * num(0, 1);
		}
		return false;
	}
	bool operator != (num b)
	{
		return !(*this == b);
	}
};
