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
int n;

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
	n = 1;
	while (n / 2 < max_val) n *= 2;
	for (int i = 0; i < n; ++i)
		w[i] = cp(cos((double)(pi * 2 * i / n)), sin((double)(pi * 2 * i / n)));
	dft(a, 0, 0);
	dft(b, 0, 0);
	for (int i = 0; i < n; ++i)
	{
		a[i] = a[i] * b[i];
		w[i].y = -w[i].y;
	}
	dft(a, 0, 0);
	for (int i = 0; i < n; ++i) c[i] = (long long)(a[i].x / n + 0.1);
	return  0;
}
