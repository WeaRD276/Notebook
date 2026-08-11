/**
 * Description: Returns the counter-clockwise ordered vertices 
 * of the half-plane intersection. Returns empty
 * if the intersection is empty. Adds a bounding
 * box to ensure a finite area.
 **/
vector<Pt> hplaneInter(vector<Line> lines)
{
	const db C = 1e9;
	lines.pb({{-C, C}, {-C, -C}});
	lines.pb({{-C, -C}, {C, -C}});
	lines.pb({{C, -C}, {C, C}});
	lines.pb({{C, C}, {-C, C}});
	sort(all(lines), [](const Line& l1, const Line& l2)
	{
		bool h1 = half(l1.n), h2 = half(l2.n);
		if (h1 != h2)
			return h1 < h2;
		int p = sgn(cross(l1.n, l2.n));
		if (p != 0)
			return p > 0;
		return sgn(l1.c / abs(l1.n)	- l2.c / abs(l2.n)) < 0;
	});
	lines.erase(unique(all(lines), parallel), lines.end());
	deque<pair<Line, Pt>> d;
	for (const Line& l : lines)
	{
		while (sz(d) > 1 && sgn(l.side((d.end() - 1)->y)) < 0)
			d.pop_back();
		while (sz(d) > 1 && sgn(l.side((d.begin() + 1)->y)) < 0)
			d.pop_front();
		if (!d.empty() && sgn(cross(d.back().x.n, l.n)) <= 0)
			return {};
		if (sz(d) < 2 || sgn(d.front().x.side(inter(l, d.back().x))) >= 0)
		{
			Pt p;
			if (!d.empty())
			{
				p = inter(l, d.back().x);
				if (!parallel(l, d.front().x))
					d.front().y = inter(l, d.front().x);
			}
			d.pb({l, p});
		}
	}
	vector<Pt> res;
	for (auto [l, p] : d)
	{
		if (res.empty() || sgn(sq(p - res.back())) > 0)
			res.pb(p);
	}
	return res;
}
