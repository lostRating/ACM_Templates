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

struct cp
{
	cp() {}
	cp(double _x, double _y): x(_x), y(_y) {}
	double x, y;
	cp operator*(const cp &b) const
	{
		return cp(x * b.x - y * b.y, x * b.y + y * b.x);
	}
};

const int N = 300000;
const double pi = asin((double)1.) * 2;

cp a[N], w[N], tt[N], wt;
long long c[N];
int n, val[N];

void dft(cp a[], int s, int t)
{
	if ((n >> t) == 1) return;
	dft(a, s, t + 1);
	dft(a, s + (1 << t), t + 1);
	for (int i = 0; i <= ((n >> (t + 1)) - 1); ++i)
	{
		int p = (i << (t + 1)) + s;
		cp &A = w[i << t];
		cp &B = a[p + (1 << t)];
		wt.x = A.x * B.x - A.y * B.y;
		wt.y = A.x * B.y + A.y * B.x;
		tt[i].x = a[p].x + wt.x;
		tt[i].y = a[p].y + wt.y;
		cp &tmp = tt[i + (n >> (t + 1))];
		tmp.x = a[p].x - wt.x;
		tmp.y = a[p].y - wt.y;
	}
	for (int i = 0; i <= ((n >> t) - 1); ++i)
		a[(i << t) + s] = tt[i];
}

int main()
{
#ifdef LOCAL_TEST
	//freopen("a.in","r",stdin);
	//freopen("a.out","w",stdout);
#endif
	int task;
	scanf("%d", &task);
	while (task--)
	{
		int N;
		scanf("%d", &N);
		for (int i = 0; i < N; ++i)
			scanf("%d", &val[i]);
		sort(val, val + N);
		n = 1;
		while (n / 2 < val[N - 1]) n *= 2;
		for (int i = 0; i < n; ++i)
		{
			w[i] = cp(cos((double)(pi * 2 * i / n)), sin((double)(pi * 2 * i / n)));
			a[i] = cp(0, 0);
			c[i] = 0;
		}
		for (int i = 0; i < N; ++i) ++a[val[i] - 1].x;
		dft(a, 0, 0);
		for (int i = 0; i < n; ++i)
		{
			a[i] = a[i] * a[i];
			w[i].y = -w[i].y;
		}
		dft(a, 0, 0);
		for (int i = 0; i < n; ++i) c[i + 2] = (long long)(a[i].x / n + 0.1);
		for (int i = 0; i < N; ++i) --c[val[i] * 2];
		for (int i = 0; i < n; ++i) c[i] /= 2;
		for (int i = 1; i < n; ++i) c[i] += c[i - 1];
		sort(val, val + N);
		long long ans = 0;
		for (int i = 0; i < N; ++i)
		{
			long long tmp = 1LL * i * (i - 1) / 2;
			ans += tmp - c[val[i]];
		}
		long long tot = 1LL * N * (N - 1) * (N - 2) / 6;
		printf("%.7f\n", 1. * ans / tot);
	}
	return 0;
}


