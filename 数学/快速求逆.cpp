int inverse(int x, int mod)
{
	if (x == 1) return 1;
	return (long long)(mod - mod / x) * inverse(mod % x, mod) % mod;
}
