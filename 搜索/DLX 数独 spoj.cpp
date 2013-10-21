/*
  Name: Soduko
  Author:  ASEMBL
  Date: 06/08/12 12:38
  Description: SPOJ Soduko
*/
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <cmath>
#include <vector>

using namespace std;
const int MAXL = 16 + 1 , MAXN = 4096+1 , MAXM = 1024+1 , SIXTEEN = 16 ;
char str[MAXL][MAXL] ;

struct Links
{
    int l , r , u , d ;
    int x , y , num ;
    int posx , posy ;
    
    Links()
    {
        l = r = u = d = x = y = num = posx = posy = 0 ;
    }
    Links(int a , int b , int xx , int yy )
    {
        posx = xx , posy = yy ;
        x = a , y = b ;
        l = r = u = d = num = 0 ;
    }
}p[(MAXM+1)*(MAXN+1)];
int colRec[MAXM] ;
int hashrow[SIXTEEN] , hashcol[SIXTEEN] , hashcube[4][4] ;
int numberInCol[MAXM] ;

bool digit( int x , int b )
{
    return 1&( x>>b ) ;
}
void constructLinkPointEdge( int current , int left , int up , Links p[] )
{
    p[current].l = left ;
    p[left].r = current ;
    p[current].u = up;
    p[up].d = current ;
}
void built()
{
    int total = 0 , rows = 0 ;
    
    memset( numberInCol , 0 , sizeof numberInCol ) ;
    memset( colRec , 0 , sizeof colRec) ;
    memset( hashrow , 0 , sizeof hashrow );
    memset( hashcol , 0 , sizeof hashcol );
    memset( hashcube , 0 , sizeof hashcube );
    //  p[0] -leftmost point in head of head_col_link
    for ( int i = 0 ; i < SIXTEEN*SIXTEEN*4 ; ++i )    //  head of cols
    {
        p[++total] = Links( rows , i , -1 , -1 );
        colRec[i] = total ;
    }
    for ( int i = 0 ; i < SIXTEEN ; ++i )
        for ( int j = 0 ; j < SIXTEEN ; ++j )
        if ( str[i][j] != '-' )
        {
            hashrow[i] |= (1<<(str[i][j]-'A')) ;
            hashcol[j] |= (1<<(str[i][j]-'A')) ;
            hashcube[i/4][j/4] |= (1<<(str[i][j]-'A')) ;
        }
    rows ++ ;
    
    for ( int i = 0 ; i < SIXTEEN ; ++i )
        for ( int j = 0 ; j < SIXTEEN ; ++j )
            if ( str[i][j] == '-' )
            for ( int k = 0 ; k < SIXTEEN ; ++k )
            {
                if ( digit( hashrow[i] , k ) || digit( hashcol[j] , k ) || digit( hashcube[i/4][j/4] , k ) )
                    continue ;
                //  self - row - col - cubes 
                p[++total] = Links( rows , i*SIXTEEN+j + SIXTEEN*SIXTEEN*0 , i , j );
                p[++total] = Links( rows , i*SIXTEEN+k + SIXTEEN*SIXTEEN*1 , i , j );
                p[++total] = Links( rows , j*SIXTEEN+k + SIXTEEN*SIXTEEN*2 , i , j );
                p[++total] = Links( rows , ((i/4)*4+j/4)*SIXTEEN+k + SIXTEEN*SIXTEEN*3 , i , j );
                
                for ( int t = 0 ; t < 4 ; ++t )
                {
                    int c = total-t ;
                    constructLinkPointEdge( c , total-(t+1)%4 , colRec[ p[c].y ] , p );
                    p[c].num = k ;
                    colRec[ p[c].y ] = c ;
                    numberInCol[ p[c].y ] ++;
                }
                rows ++ ;
            }
    for ( int y = 0 ; y < SIXTEEN*SIXTEEN*4 ; ++y )
        constructLinkPointEdge( y+1 , y , colRec[y] , p );
    p[0].l = SIXTEEN*SIXTEEN*4 ;
    p[SIXTEEN*SIXTEEN*4].r = 0 ;
    //  getout of zero-cols
    for ( int i = p[0].r ; i ; i = p[i].r )
    {
        if ( numberInCol[ p[i].y ] == 0 )
        {
            p[ p[i].l ].r = p[i].r ;
            p[ p[i].r ].l = p[i].l ;
        }
    }
}
void del( int start )    //  start - number of head lines
{
    for ( int i = p[start].d ; i != start ; i = p[i].d )
        for ( int j = p[i].r ; j != i ; j = p[j].r )
        {
            p[ p[j].d ].u = p[j].u ;
            p[ p[j].u ].d = p[j].d ;
            numberInCol[ p[j].y ] -- ;
        }
    p[ p[start].l ].r = p[start].r ;
    p[ p[start].r ].l = p[start].l ;
}
void back( int start )   //  start - number of head lines
{
    for ( int i = p[start].u ; i != start ; i = p[i].u )
        for ( int j = p[i].l ; j != i ; j = p[j].l )
        {
            p[ p[j].d ].u = j ;
            p[ p[j].u ].d = j ;
            numberInCol[ p[j].y ] ++ ;
        }
    p[ p[start].l ].r = start ;
    p[ p[start].r ].l = start ;
}
bool dfs( int deep )
{
    int min = -1 ;
    
    if ( p[0].r == 0 )
        return true ;
    for ( int i = p[0].r ; i ; i = p[i].r )
        if ( min == -1 || numberInCol[ p[i].y ] < numberInCol[ p[min].y ] )
            min = i ;
    del( min );
    for ( int i = p[min].d ; i != min ; i = p[i].d )
    {
        for ( int j = p[i].r ; j != i ; j = p[j].r )
            del( p[j].y+1 );
        str[ p[i].posx ][ p[i].posy ] = p[i].num + 'A' ;
        
        if ( dfs( deep+1 ) )
            return true ;
        for ( int j = p[i].l ; j != i ; j = p[j].l )
            back( p[j].y+1 );
    }
    back( min );
    return false ;
}

int main()
{
    int test ;
    
    for ( scanf("%d",&test) ; test-- ; )
    {
        for ( int i = 0 ; i < SIXTEEN ; ++i )
            scanf("%s",str[i]);
        built();
        dfs(0);
        for ( int i = 0 ; i < SIXTEEN ; ++i )
            printf("%s\n",str[i]);
        if ( test )
            printf("\n");
    }
    
    return 0;
}
