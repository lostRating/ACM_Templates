const int MAXN = 100001;

char str1[MAXN] , str2[MAXN] ;
int next1[MAXN] , next2[MAXN] ;

void exkmp( char *s1 , char *s2 , int next1[] , int next2[] )
{
    int l1 = strlen( s1 ) , l2 = strlen( s2 ) ;
    for ( int j = 0 ; true ; ++j )
        if ( s2[j] != s1[j] || j == l2 || j == l1 )
        {
            next2[0] = j ;
            break;
        }
    int best = 0 , mx = 0 ;
    for ( int i = 1 ; i < l2 ; ++i )
    {
        int st ;
        if ( i >= mx )
            st = 0 ;
        else
            st = min( mx-i , next1[ i-best ] );
        for ( int j = st ; true ; ++j )
            if ( s2[i+j] != s1[j] || j == l1 || i+j == l2 )
            {
                next2[i] = j ;
                break;
            }
        if ( i+next2[i] > mx )
            best = i , mx = i+next2[i] ;
    }
}

int main()
{
    scanf("%s%s",str1,str2);
    exkmp( str1 , str1 , next1 , next1 );
    exkmp( str1 , str2 , next1 , next2 );
    int l1 = strlen( str1 ) , l2 = strlen( str2 ) ;
    for ( int j = 0 ; j < l2 ; ++j )
    {
        for ( int k = 0 ; k < next2[j] ; ++k )
            if ( str1[k] != str2[j+k] )
                printf("error\n");
    }
    return 0;
}
/*
ababa
ababab
*/
