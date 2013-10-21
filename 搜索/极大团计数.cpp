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

const int N = 255;

bool g[N][N];
int ne[N], ce[N], list[N][N], ans;

void dfs(int size)
{
	if (ans > 1000) return;
	int i, j, k, t, cnt, best = 0;
	bool bb;
	if (ne[size] == ce[size])
	{
		if (ce[size] == 0) ++ans;
		return;
	}
	for (t = 0, i = 1; i <= ne[size]; ++i)
	{
		for (cnt = 0, j = ne[size] + 1; j <= ce[size]; ++j)
			if (!g[list[size][i]][list[size][j]]) ++cnt;
		if (t == 0 || cnt < best) t = i, best = cnt;
	}
	if (t && best <= 0) return;
	for (k = ne[size] + 1; k <= ce[size]; ++k)
	{
		if (t > 0)
		{
			for (i = k; i <= ce[size]; ++i)
				if (!g[list[size][t]][list[size][i]]) break;
			swap(list[size][k], list[size][i]);
		}
		i = list[size][k];
		ne[size + 1] = ce[size + 1] = 0;
		for (j = 1; j < k; ++j)
			if (g[i][list[size][j]])
				list[size + 1][++ne[size + 1]] = list[size][j];
		for (ce[size + 1] = ne[size + 1], j = k + 1; j <= ce[size]; ++j)
			if (g[i][list[size][j]]) list[size + 1][++ce[size + 1]] = list[size][j];
		dfs(size + 1);
		++ne[size];
		--best;
		for (j = k + 1, cnt = 0; j <= ce[size]; ++j)
			if (!g[i][list[size][j]]) ++cnt;
		if (t == 0 || cnt < best) t = k, best = cnt;
		if (t && best <= 0) break;
	}
}

int main(){
	int n, m;
	while (scanf("%d%d", &n, &m) == 2)
	{
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= n; ++j)
				g[i][j] = false;
		while (m--)
		{
			int x, y;
			scanf("%d%d", &x, &y);
			g[x][y] = g[y][x] = true;
		}
		ne[0] = 0;
		ce[0] = 0;
		for (int i = 1; i <= n; ++i)
			list[0][++ce[0]] = i;
		ans = 0;
		dfs(0);
		if (ans > 1000)
			puts("Too many maximal sets of friends.");
		else
			printf("%d\n", ans);
	}
	return 0;
}

