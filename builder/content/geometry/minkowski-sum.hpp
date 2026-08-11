/**
 * Description: Returns the Minkowski sum of two convex polygons.
 **/
vector<Pt> minkowskiSum(const vector<Pt>& v1, const vector<Pt>& v2)
{
	if (v1.empty() || v2.empty())
		return {};
	if (sz(v1) == 1 && sz(v2) == 1)
		return {v1[0] + v2[0]};
	auto comp = [](const Pt& p, const Pt& q)
	{
		return sgn(p.x - q.x) < 0
			|| (sgn(p.x - q.x) == 0
			&& sgn(p.y - q.y) < 0);
	};
	int i1 = min_element(all(v1), comp) - v1.begin();
	int i2 = min_element(all(v2), comp)	- v2.begin();
	vector<Pt> res;
	int n1 = sz(v1), n2 = sz(v2),
		j1 = 0, j2 = 0;
	while (j1 < n1 || j2 < n2)
	{
		const Pt& p1 = v1[(i1 + j1) % n1];
		const Pt& q1 = v1[(i1 + j1 + 1) % n1];
		const Pt& p2 = v2[(i2 + j2) % n2];
		const Pt& q2 = v2[(i2 + j2 + 1) % n2];
		if (sz(res) >= 2 && onSegment(res[sz(res) - 2], p1 + p2, res.back()))
			res.pop_back();
		res.pb(p1 + p2);
		int s = sgn(cross(q1 - p1, q2 - p2));
		if (j1 < n1 && (j2 == n2 || s > 0
			|| (s == 0 && (sz(res) < 2
			|| sgn(dot(res.back()
			- res[sz(res) - 2],
			q1 + p2 - res.back())) > 0))))
			j1++;
		else
			j2++;
	}
	if (sz(res) > 2	&& onSegment(res[sz(res) - 2], res[0], res.back()))
		res.pop_back();
	return res;
}
