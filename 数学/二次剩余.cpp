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

vector<int> ans;

int pow_mod(int i, int j, int p)
{
	if (j == 0) return 1;
	if (j % 2 == 1) return i * pow_mod(i, j - 1, p) % p;
	long long t = pow_mod(i, j / 2, p);
	return t * t % p;
}

inline int my_sqr(int x)
{
	return x * x;
}

inline bool quad_resi(int x, int p)
{
	return pow_mod(x, (p - 1) / 2, p) == 1;
}

struct quad_poly
{
	int zero, one, val, mod;

	quad_poly(int zero, int one, int val, int mod):zero(zero), one(one), val(val), mod(mod) {}

	quad_poly multiply(quad_poly o)
	{
		int z0 = (zero * o.zero + one * o.one % mod * val % mod) % mod;
		int z1 = (zero * o.one + one * o.zero) % mod;
		return quad_poly(z0, z1, val, mod);
	}

	quad_poly pow(int x)
	{
		if (x == 1) return *this;
		quad_poly ret = this->pow(x / 2);
		ret = ret.multiply(ret);
		if (x & 1)
			ret = ret.multiply(*this);
		return ret;
	}
};

int cal(int a, int p)
{
	if (a < 2) return a;
	if (!quad_resi(a, p)) return p;
	if (p % 4 == 3) return pow_mod(a, (p + 1) / 4, p);
	int b = 0;
	while (quad_resi((my_sqr(b) - a + p) % p, p))
		b = rand() % p;
	quad_poly ret = quad_poly(b, 1, (my_sqr(b) - a + p) % p, p);
	ret = ret.pow((p + 1) / 2);
	return ret.zero;
}

int main(){
	srand(time(0));
	int task;
	scanf("%d", &task);
	while (task--)
	{
		int a, p;
		scanf("%d%d", &a, &p);
		int ans = cal(a, p);
		if (ans == p)
		{
			puts("No root");
		}
		else
		{
			int hehe = p - ans;
			if (ans > hehe) swap(ans, hehe);
			printf("%d", ans);
			if (ans != hehe) printf(" %d", hehe);
			puts("");
		}
	}
	return 0;
}
