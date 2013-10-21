#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std ;
const int MAXL = 2000001 ;

char str[MAXL];
int n , ans[MAXL] ;

int LogestPalindrome( char *str , int n )
{
    str[2*n] = '\0' ;
    for ( int i = n-1 ; i >= 0 ; --i )
    {
        str[2*i+1] = str[i] ;
        str[2*i] = '#' ;
    }
    
    n *= 2 ;
    
    ans[0] = 1 ;
    int best = 0 , mx = ans[0] , res = 0 ;
    
    for ( int i = 1 ; i < n ; ++i )
    {
        int st = ( i >= mx ? 1 : min( mx-i , ans[2*best-i] ) ) ;
        
        for ( int j = st ; true ; ++j )
            if ( i+j == n || i-j < 0 || str[i+j] != str[i-j] )
            {
                ans[i] = j ;
                break;
            }
        if ( mx < ans[i]+i )
            best = i , mx = ans[i]+i ;
    }
    for ( int i = 0 ; i < n ; ++i )
    {
        if ( i&1 )
            res = max( res , ans[i]-!(ans[i]&1) ) ;
        else
            res = max( res , ans[i]-(ans[i]&1) );
    }
    return res ;
}

int main()
{
    int test = 0 ;
    
    while(1)
    {
        scanf("%s",str);
        n = strlen( str ) ;
        if ( n == 3 && str[0] == 'E' && str[1] == 'N' && str[2] == 'D' )
            break;
        
        printf("Case %d: %d\n",++test,LogestPalindrome( str , n ) );
    }
    return 0;
}
