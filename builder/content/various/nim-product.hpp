/**
 * Description: The Nim sum $\oplus$: $a \oplus b := \text{mex} (\{a' \oplus b | a' < a\} \cup \{a \oplus b' | b' < b\})$.
 * The Nim product $\otimes$: $a \otimes b := \text{mex} \{(a' \otimes b) \oplus (a \otimes b') \oplus (a' \otimes b') | a' < a, b' < b\}$.
 * Let $A$ be the set consisting of integers between $0$ (inclusive) and $2^{2^n}$ (exclusive) (where $n$ is an integer).
 * Then the algebraic structure whose addition is $\oplus$ and multiplication is $\otimes$ forms a field. Such a field is called \textbf{Nimber}.
 * Time: About 64 references to the precalculation table.
 */
typedef unsigned long long ull;

const int S = 8;

int small[1 << S][1 << S];

void init()
{
	FOR(i, 0, 1 << S)
		FOR(j, 0, 1 << S)
			small[i][j] = -1;
}

ull nimProduct(ull a, ull b, int p = 64)
{
	if (min(a, b) <= 1)
		return a * b;
	if (p <= S && small[a][b] != -1)
		return small[a][b];
	p >>= 1;
	ull a1 = a >> p, a2 = a & ((1ULL << p) - 1);
	ull b1 = b >> p, b2 = b & ((1ULL << p) - 1);
	ull c = nimProduct(a1, b1, p);
	ull d = nimProduct(a2, b2, p);
	ull e = nimProduct(a1 ^ a2, b1 ^ b2, p);
	ull res = nimProduct(c, 1ULL << (p - 1), p) ^ d ^ ((d ^ e) << p);
	if (p <= S / 2)
		small[a][b] = res;
	return res;
}
