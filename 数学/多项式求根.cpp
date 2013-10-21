#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
#define sz(X) ((int)((X).size()))
#define pb push_back
const double eps = 1e-12;
double a[10][10];
typedef vector<double> vd;
int sgn(double x){return x < -eps ? -1 : x > eps;}
double mypow(double x, int num)
{
	double ans = 1.0;
	while (num--) ans *= x;
	return ans;
}
double f(int n, double x)
{
	double ans = 0;
	for (int i = n; i >= 0; --i)
		ans += a[n][i] * mypow(x, i);
	return ans;
}
double getRoot(int n, double l, double r)
{
	if (sgn(f(n, l)) == 0) return l;
	if (sgn(f(n, r)) == 0) return r;
	double temp;
	if (sgn(f(n, l)) > 0) temp = -1; else temp = 1;
	double m;
	for (int i = 1; i <= 10000; ++i)
	{
		m = (l + r) / 2;
		double mid = f(n, m);
		if (sgn(mid) == 0) return m;
		if (mid * temp < 0) l = m; else r = m;
	}
	return (l + r) / 2;
}
vd did(int n)
{
	vd ret;
	if (n == 1)
	{
		ret.pb(-1e10);
		ret.pb(-a[n][0] / a[n][1]);
		ret.pb(1e10);
		return ret;
	}
	vd mid = did(n - 1);
	ret.pb(-1e10);
	for (int i = 0; i + 1 < sz(mid); ++i)
	{
		int t1 = sgn(f(n, mid[i]));
		int t2 = sgn(f(n, mid[i + 1]));
		if (t1 * t2 > 0) continue;
		ret.pb(getRoot(n, mid[i], mid[i + 1]));
	}
	ret.pb(1e10);
	return ret;
}
int main()
{
	int n; scanf("%d", &n);
	for (int i = n; i >= 0; --i)
		scanf("%lf", &a[n][i]);
	for (int i = n - 1; i >= 0; --i)
		for (int j = 0; j <= i; ++j)
			a[i][j] = a[i + 1][j + 1] * (j + 1);
	vd ans = did(n);
	sort(ans.begin(), ans.end());
	for (int i = 1; i + 1 < sz(ans); ++i)
		printf("%.10f\n", ans[i]);
	return 0;
}
