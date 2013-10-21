const int N = 80005;

vector<pair<int, int> > point[N];
int v[N], d[N], match[N], tt, l[N];

bool find(int i)
{
	if (v[i] == tt) return 0;
	v[i] = tt;
	for (int k = 0; k < sz(point[i]); ++k)
	{
		int j = point[i][k].first;
		if (d[i] + 1 != d[j]) continue;
		if (match[j] == 0 || find(match[j]))
		{
			match[i] = j;
			match[j] = i;
			return 1;
		}
	}
	return 0;
}

int main(){
	int n1, n2, m;
	while (scanf("%d%d%d", &n1, &n2, &m) == 3)
	{
		for (int i = 1; i <= n1 + n2 + 2; ++i)
		{
			point[i].clear();
			match[i] = 0;
		}
		for (int i = 0; i < m; ++i)
		{
			int x = get();
			int y = get() + n1;
			point[x].pb(mp(y, i));
			point[y].pb(mp(x, i));
		}
		while (1)
		{
			int op = 0, ed = 0;
			for (int i = 1; i <= n1 + n2; ++i)
			{
				d[i] = -1;
				if (match[i] == 0 && i > n1)
				{
					++ed;
					l[ed] = i;
					d[i] = 0;
				}
			}
			while (op < ed)
			{
				++op;
				int i = l[op];
				if (i > n1)
				{
					for (int k = 0; k < sz(point[i]); ++k)
					{
						int j = point[i][k].first;
						if (d[j] == -1)
						{
							d[j] = d[i] + 1;
							if (match[j] != 0)
							{
								++ed;
								l[ed] = j;
							}
						}
					}
				}
				else if (match[i] != 0)
				{
					++ed;
					l[ed] = match[i];
					d[match[i]] = d[i] + 1;
				}
			}
			int ok = 0;
			++tt;
			for (int i = n1 + 1; i <= n1 + n2; ++i)
				if (match[i] == 0 && find(i))
					ok = 1;
			if (ok == 0) break;
		}
	}
	return 0;
}
