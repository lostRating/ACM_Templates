#include <cstdio>
#include <algorithm>
#include <iostream>
using namespace std ;
typedef long long LL ;
int N ;
LL fac[100000] ;

LL mod_mul( LL x , LL y , LL n ) {
    LL d = (LL)((long double)x*y/n);
    d = x*y-n*d ;
    while (d<0) d+=n;
    while (d>=n) d-=n ;
    return d;
}

LL powmod(LL a,LL b,LL mod) {
    LL res=1;
    while (b) {
        if(b&1) {
            res=mod_mul(res,a,mod);
        }
        a=mod_mul(a,a,mod);
        b>>=1;
    }
    return res;
}
int strong_pseudo_primetest(LL n,int base) {
    LL n2=n-1,res;
    int s=0;
    while(n2%2==0) n2>>=1,++s ;
    res=powmod( base,n2,n);
    if((res==1)||(res==n-1)) return 1;
    --s;
    while(s>=0) {
        res = mod_mul(res,res,n) ;
        if(res==n-1) return 1 ;
        --s ;
    }
    return 0; // n is not a strong pseudo prime
}

int isPrime(LL n) {
    if (n<2) return 0;
    if (n<4) return 1;
    if (strong_pseudo_primetest(n,2)==0) return 0;
    if (strong_pseudo_primetest(n,3)==0) return 0;
    if (n<1373653LL) return 1;
    if (strong_pseudo_primetest(n,5)==0) return 0;
    if (n<25326001LL) return 1;
    if (strong_pseudo_primetest(n,7)==0) return 0;
    if (n==3215031751LL) return 0;
    if (n<25000000000LL) return 1;
    if (strong_pseudo_primetest(n,11)==0) return 0;
    if (n<2152302898747LL) return 1;
    if (strong_pseudo_primetest(n,13)==0) return 0;
    if (n<3474749660383LL) return 1;
    if (strong_pseudo_primetest(n,17)==0) return 0;
    if (n<341550071728321LL) return 1;
    if (strong_pseudo_primetest(n,19)==0) return 0;
    if (strong_pseudo_primetest(n,23)==0) return 0;
    if (strong_pseudo_primetest(n,29)==0) return 0;
    if (strong_pseudo_primetest(n,31)==0) return 0;
    if (strong_pseudo_primetest(n,37)==0) return 0;
    return 1;
}
LL myAbs(LL x) {
    return x>0?x:-x;
}
LL gcd(LL a,LL b) {
    if (b) return gcd(b,a%b) ;
    return a ;
}
LL pollardRho(LL n,LL c)//  return a non-trival factor of n , otherwise n
{
    LL x,y;
    x=y=rand()%(n-1)+1;
    LL head=1,tail=2;
    while(1) {
        x=mod_mul(x,x,n);
        x+=c;
        if(x>=n) x-=n;
        if(x==y) return n;
        LL d=gcd(myAbs(x-y),n);
        if(d>1&&d<n) return d;
        if((++head)==tail) {
            y=x;
            tail<<=1;
        }
    }
}

void factor(LL n)
{
    if(n<=1) return ;
    if(isPrime(n)) {
        if(N>100) while(1);
        fac[N++]=n;
        return ;
    }
    LL p=n;
    while(p>=n) p=pollardRho(n,rand()%(n-1)+1);
    factor(n/p);
    factor(p);
}

int main()
{
    int T ;

    scanf("%d",&T);
    while(T--) {
        N = 0 ;
        LL x;
        cin >> x ;
        if ( isPrime(x) )
            puts("Prime");
        else
        {
            factor(x);
            LL ans=x;
            for(int i=0;i<N;++i) if(fac[i]<ans) ans=fac[i];
            cout<<ans<<'\n' ;
        }
    }

    return 0;
}
