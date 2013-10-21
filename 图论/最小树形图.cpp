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

using namespace std;

typedef long long int64;
typedef long double real;

#define mp make_pair
#define pb push_back
#define sz(X) ((int)((X).size()))

const double eps = 1e-6;
const int lim = 1000000000;

const int N = 105;

bool ok;
int n, pre[N], f[N], use[N], L[N];
double d[N][N], ans;
vector<double> vec[N];

inline double sqr(double x)
{
	return x * x;
}

void cutcircle()
{
	ok = false;
	for (int i = 0; i <= n; ++i) pre[i] = i;
	for (int i = 0; i <= n; ++i) if (f[i] == i)
		for (int j = 0; j <= n; ++j) if (f[j] == j && d[i][j] < d[pre[j]][j])
			pre[j] = i;
	for (int i = 1; i <= n; ++i) if (f[i] == i)
	{
		int j = i;
		memset(use, 0, sizeof use);
		while (j != 0 && !use[j])
		{
			use[j] = true;
			j = pre[j];
		}
		if (j == i)
		{
			ok = true;
			int ed = 1;
			L[ed] = j;
			ans += d[pre[j]][j];
			j = pre[j];
			while (j != i)
			{
				ans += d[pre[j]][j];
				++ed;
				L[ed] = j;
				f[j] = i;
				j = pre[j];
			}
			for (j = 0; j <= n; ++j) if (f[j] == j && j != i)
			{
				double t1 = 1e20;
				double t2 = 1e20;
				for (int k = 1; k <= ed; ++k)
				{
					t1 = min(t1, d[L[k]][j]);
					t2 = min(t2, d[j][L[k]] - d[pre[L[k]]][L[k]]);
				}
				d[i][j] = t1;
				d[j][i] = t2;
			}
		}
		if (ok) return;
	}
}

double len(const vector<double> &a)
{
	double ret = 0;
	for (int i = 0; i < sz(a); ++i)
		ret += sqr(a[i]);
	return ret;
}

double cal(const vector<double> &a, const vector<double> &b)
{
	double ret = 0, p = 0, q = 0;
	for (int i = 0; i < sz(a); ++i)
	{
		p += a[i] * b[i];
		q += sqr(b[i]);
	}
	double r;
	if (fabs(q) < eps) r = 0;
	else r = p / q;
	vector<double> c = a;
	for (int i = 0; i < sz(a); ++i)
		c[i] = a[i] - r * b[i];
	return len(c);
}

int main()
{
	int m;
	scanf("%d%d", &m, &n);
	for (int i = 1; i <= n; ++i)
		for (int j = 0; j < m; ++j)
		{
			double x;
			scanf("%lf", &x);
			vec[i].pb(x);
		}
	for (int i = 1; i <= n; ++i)
	{
		d[0][i] = len(vec[i]);
		for (int j = 1; j <= n; ++j)
			d[j][i] = cal(vec[i], vec[j]);
		d[i][i] = 1e20;
	}
	for (int i = 0; i <= n; ++i) f[i] = i;
	ans = 0;
	ok = true;
	while (ok) cutcircle();
	for (int i = 1; i <= n; ++i)
		if (f[i] == i)
			ans += d[pre[i]][i];
	printf("%.10f\n", ans);
	return  0;
}


