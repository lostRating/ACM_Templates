long long solve( long long n , long long a , long long b , long long m )
//  for ( int i = 0 ; i < n ; ++i) s+=floor((a+b*i)/m);
//  n,m,a,b>0
{
    if (b == 0) return n*(a/m);
    if (a >= m) return n*(a/m) + solve(n,a%m,b,m);
    if (b >= m) return (n-1)*n/2*(b/m) + solve(n,a,b%m,m);
    long long q = (a+b*n)/m;
    return solve(q,(a+b*n)%m,m,b);
}
