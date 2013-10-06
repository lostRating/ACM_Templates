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
#include <bitset>
#include <iomanip>

using namespace std;

typedef long long int64;
typedef long long LL;
typedef long double real;
typedef long double LD;

#define mp make_pair
#define PII pair<int, int>
#define pb push_back
#define sz(X) ((int)((X).size()))

const double eps = 1e-8;
const double PI = acos(0.) * 2;
const int lim = 1000000000;
const int inf = ~0U >> 1;

template<class T> T abs(T x){return x < 0 ? -x : x;}

const int N = 105;
const int M = 1005;

vector<pair<int, int> > edge[N];
double a[M + N][N];
int f[N], next[N];

int dfs(int a)
{
	if (f[a] != -1) return f[a];
	f[a] = 0;
	for (int i = 0; i < sz(edge[a]); ++i)
		f[a] = max(f[a], dfs(edge[a][i].first) + edge[a][i].second);
	return f[a];
}

int main()
{
	#ifdef LOCAL_TEST
		freopen("c.in","r",stdin);
//		freopen("c.out","w",stdout);
	#endif
	int n, m, ans = 0;
	cin >> n >> m;
	for (int i = 1; i <= m; ++i)
	{
		int u, v, w;
		cin >> u >> v >> w;
		++u;
		++v;
		edge[v].pb(mp(u, w));
		a[i + n][v] = 1;
		a[i + n][u] = -1;
		a[i + n][0] = -w;
		ans -= w;
		++a[0][v];
		++a[0][u];
	}
	for (int i = 1; i <= n; ++i)
		f[i] = -1;
	for (int i = 1; i <= n; ++i)
	{
		a[i][i] = -1;
		a[i][0] = dfs(n);
	}
	int tmp = n;
	n = n + m;
	m = tmp;
	// maximum
	// sigma row >= 0
	// row 0~n	row 0 is target function
	// col 0~m	col 0 is constant
	while (1)
	{
		int i;
		for (i = 1; i <= m + 1; ++i)
			if (a[0][i] > eps) break;
		if (i > m) break;
		double Min = 1e30;
		int k;
		for (int j = 1; j < n; ++j)
			if (a[j][i] < -eps && a[j][0] / -a[j][i] < Min)
			{
				Min = a[j][0] / - a[j][i];
				k = j;
			}
		double t = -1. / a[k][i];
		a[k][i] = -1;
		for (int j = 0; j <= m; ++j)
			a[k][j] = a[k][j] * t;
		int tt = -1;
		for (int j = 0; j <= m; ++j)
			if (fabs(a[k][j]) > eps)
			{
				next[j] = tt;
				tt = j;
			}
		for (int j = 0; j <= n; ++j)
		{
			if (j == k) continue;
			t = a[j][i];
			a[j][i] = 0;
			int p = tt;
			while (p != -1)
			{
				a[j][p] = a[j][p] + t * a[k][p];
				p = next[p];
			}
		}
	}
	printf("%.3f\n", a[0][0] + ans);
    return 0;
}
