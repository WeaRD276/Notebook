// 34a7ec for min_left 

// If f is monotone, this is the maximum r that satisfies
// 	f(op(a[l], a[l + 1], ..., a[r - 1])) = true
template<class G>
int max_right(int l, G g)
{
	if (l == n) return n;
	assert(g(e()));
	l += size;
	RFOR(i, log + 1, 1) push(l >> i);
	S sm = e();
	do
	{
		while ((l & 1) == 0) l >>= 1;
		if (!g(op(sm, t[l])))
		{
			while (l < size)
			{
				push(l);
				l = (l << 1);
				if (g(op(sm, t[l])))
				{
					sm = op(sm, t[l]);
					l++;
				}
			}
			return l - size;
		}
		sm = op(sm, t[l]);
		l++;
	} while ((l & -l) != l);
	return n;
}

// If f is monotone, this is the minimum l that satisfies 
//   f(op(a[l], a[l + 1], ..., a[r - 1])) = true
//template<class G>
//int min_left(int r, G g)
//{
	//if (r == 0) return 0;
	//assert(g(e()));
	//r += size;
	//RFOR(i, log + 1, 1) push((r - 1) >> i);
	//S sm = e();
	//do
	//{
		//r--;
		//while (r > 1 && (r & 1)) r >>= 1;
		//if (!g(op(t[r], sm)))
		//{
			//while (r < size)
			//{
				//push(r);
				//r = (r << 1) | 1;
				//if (g(op(t[r], sm)))
				//{
					//sm = op(t[r], sm);
					//r--;
				//}
			//}
			//return r + 1 - size;
		//}
		//sm = op(t[r], sm);
	//} while ((r & -r) != r);
	//return 0;
//}
