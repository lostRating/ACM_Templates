#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <map>
#include <set>
#include <queue>
#include <deque>
#include <ctime>
#include <sstream>
#include <fstream>
#include <assert.h>

using namespace std;

typedef long long int64;

#define FOR(i,a,b) for(int i=(a);i<=(b);++i)
#define ROF(i,a,b) for(int i=(a);i>=(b);--i)
#define mp make_pair
#define pb push_back
#define fi first
#define se second
#define sz(a) ((int)(a).size())
#define ms(a,x)

const int inf = 1000000000;
const int N = 10005;
const int M = 10005 * 50;

bool v[N], o[N];
int s, t, ed, cost, p[4][N];
int dis[N], f[N], ne[N];
int now[M], point[M], pos[M], key1[M], key2[M], next[M];

void link(int a, int b, int c, int d)
{
	++ed; next[now[a]] = ed; now[a] = ed; point[ed] = b;
	key1[ed] = c; key2[ed] = d; pos[ed] = ed + 1;
	++ed; next[now[b]] = ed; now[b] = ed; point[ed] = a;
	key1[ed] = 0; key2[ed] = -d; pos[ed] = ed - 1;
}

int dfs(int a, int flow)
{
	if (a == t)
	{
		cost += dis[a];
		return flow;
	}
	int i = ne[a];
	int j = point[i];
	int ret = 0;
	o[a] = true;
	v[a] = true;
	while (i)
	{
		int l = dis[a] + key2[i] - dis[j];
		int Min = min(flow, key1[i]);
		if (Min)
			f[j] = min(f[j], l);
		if (Min && !l && !o[j])
		{
			l = dfs(j, Min);
			ret += l;
			flow -= l;
			key1[i] -= l;
			key1[pos[i]] += l;
		}
		if (flow == 0) break;
		ne[a] = next[ne[a]];
		i = ne[a];
		j = point[i];
	}
	o[a] = false;
	return ret;
}

int main()
{
	#ifdef LOCAL_TEST
		freopen("c.in","r",stdin);
//		freopen("c.out","w",stdout);
	#endif
	int n, m;
	scanf("%d%d", &n, &m);
	for (int i = 0; i < m; ++i)
		for (int j = 1; j <= n; ++j)
		{
			int x;
			scanf("%d", &x);
			p[i][x] = j;
		}
	s = n * 2 + 1;
	t = s + 1;
	ed = t;
	for (int i = 1; i <= t; ++i) now[i] = i;
	for (int i = 1; i <= n; ++i)
	{
		link(s, i, 1, 0);
		link(i, t, 1, 8 * m);
		link(i + n, t, 1, 0);
		set<int> a;
		for (int j = 0; j < m; ++j)
			for (int k = max(1, p[j][i] - 7); k <= min(n, p[j][i] + 7); ++k)
				a.insert(k);
		set<int>::iterator j = a.begin();
		for (; j != a.end(); ++j)
		{
			int dis = 0;
			for (int k = 0; k < m; ++k)
				dis += min(8, abs(p[k][i] - (*j)));
			link(i, (*j) + n, 1, dis);
		}
	}
	while (1)
	{
		for (int i = 1; i <= t; ++i)
		{
			ne[i] = next[i];
			f[i] = inf;
			v[i] = false;
		}
		dfs(s, inf);
		int imp = inf;
		for (int i = 1; i <= t; ++i)
			if (!v[i])
				imp = min(imp, f[i]);
		if (imp == inf) break;
		for (int i = 1; i <= t; ++i)
			if (!v[i])
				dis[i] += imp;
	}
	printf("%d\n", cost);
	return 0;
}
