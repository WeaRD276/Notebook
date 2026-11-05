// 8bee60 for min_left

// If g is monotone, this is the maximum r that satisfies
// 	g(op(a[l], a[l + 1], ..., a[r - 1])) = true
template<class G>
int max_right(int l, G g)
{
	if (l == size) 
		return size;
	assert(g(Node()));
	l += n;
	RFOR(i, lg + 1, 1) // lazy
		push(l >> i); // lazy
	Node sm;
	do
	{
		while ((l & 1) == 0) 
			l >>= 1;
		if (!g(op(sm, t[l])))
		{
			while (l < n)
			{
				push(l); // lazy
				l = (l << 1);
				if (g(op(sm, t[l])))
				{
					sm = op(sm, t[l]);
					l++;
				}
			}
			return l - n;
		}
		sm = op(sm, t[l]);
		l++;
	} while ((l & -l) != l);
	return size;
}

// If g is monotone, this is the minimum l that satisfies
//   g(op(a[l], a[l + 1], ..., a[r - 1])) = true
//template<class G>
//int min_left(int r, G g)
//{
	//if (r == 0) 
		//return 0;
	//assert(g(Node()));
	//r += n;
	//RFOR(i, lg + 1, 1) // lazy
		//push((r - 1) >> i); // lazy
	//Node sm;
	//do
	//{
		//r--;
		//while (r > 1 && (r & 1)) 
			//r >>= 1;
		//if (!g(op(t[r], sm)))
		//{
			//while (r < n)
			//{
				//push(r); // lazy
				//r = (r << 1) | 1;
				//if (g(op(t[r], sm)))
				//{
					//sm = op(t[r], sm);
					//r--;
				//}
			//}
			//return r + 1 - n;
		//}
		//sm = op(t[r], sm);
	//} while ((r & -r) != r);
	//return 0;
//}
