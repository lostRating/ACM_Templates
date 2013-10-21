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

const int N = 80005;

vector<pair<int, int> > point[N];
vector<int> edge[N], EDGE[N];
int v[N], d[N], match[N], tt, l[N];
int ED, visit[N], color[N];

int get()
{
	int ret = 0;
	for (int i = 0; i < 3; ++i)
	{
		ret *= 32;
		char c;
		scanf(" %c", &c);
		if ('0' <= c && c <= '9')  ret += c - '0';
		else ret += c - 'A' + 10;
	}
	return ret + 1;
}

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

void dfs(int i)
{
	if (visit[i]) return;
	visit[i] = true;
	for (int k = 0; k < sz(edge[i]); ++k)
	{
		int j = edge[i][k];
		dfs(j);
	}
	++ED;
	l[ED] = i;
}

void dfs(int i, int col)
{
	if (visit[i]) return;
	visit[i] = true;
	for (int k = 0; k < sz(EDGE[i]); ++k)
	{
		int j = EDGE[i][k];
		dfs(j, col);
	}
	color[i] = col;
}

int main(){
	int n1, n2, m;
	while (scanf("%d%d%d", &n1, &n2, &m) == 3)
	{
		for (int i = 1; i <= n1 + n2 + 2; ++i)
		{
			point[i].clear();
			edge[i].clear();
			EDGE[i].clear();
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
		set<pair<int, int> > match_edge;
		for (int i = 1; i <= n1; ++i)
			if (match[i] != 0)
				match_edge.insert(mp(i, match[i]));
		int S = n1 + n2 + 1;
		int T = S + 1;
		for (int i = n1 + 1; i <= n1 + n2; ++i)
		{
			if (match[i] != 0)
			{
				edge[i].pb(T);
				EDGE[T].pb(i);
			}
			else
			{
				edge[T].pb(i);
				EDGE[i].pb(T);
			}
		}
		for (int i = 1; i <= n1; ++i)
		{
			if (match[i] != 0)
			{

				edge[S].pb(i);
				EDGE[i].pb(S);
			}
			else
			{
				edge[i].pb(S);
				EDGE[S].pb(i);
			}
		}
		vector<pair<pair<int, int>, int> > gxx;
		for (int i = 1; i <= n1; ++i)
			for (int k = 0; k < sz(point[i]); ++k)
			{
				int j = point[i][k].first;
				if (match_edge.count(mp(i, j)))
				{
					edge[i].pb(j);
					EDGE[j].pb(i);
				}
				else
				{
					gxx.pb(mp(mp(i, j), point[i][k].second));
					edge[j].pb(i);
					EDGE[i].pb(j);
				}
			}
		ED = 0;
		for (int i = 1; i <= n1 + n2 + 2; ++i) visit[i] = false;
		for (int i = 1; i <= n1 + n2 + 2; ++i)
			dfs(i);
		for (int i = 1; i <= n1 + n2 + 2; ++i) visit[i] = false;
		for (int i = n1 + n2 + 2; i; --i)
			dfs(l[i], l[i]);
		vector<int> hehe;
		for (int i = 0; i < sz(gxx); ++i)
			if (color[gxx[i].first.first] != color[gxx[i].first.second])
				hehe.pb(gxx[i].second);
		sort(hehe.begin(), hehe.end());
		printf("%d\n", sz(hehe));
		for (int i = 0; i < sz(hehe); ++i)
		{
			if (i) printf(" ");
			printf("%d", hehe[i]);
		}
		printf("\n");
	}
	return 0;
}
