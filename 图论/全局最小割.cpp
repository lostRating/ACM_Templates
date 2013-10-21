/*对于图中任意两点s和t, 它们要么属于最小割的两个不同集中, 要么属于同一个集.
如果是后者, 那么合并s和t后并不影响最小割. 基于这么个思想, 如果每次能求出图中某两点之间的最小割, 然后更新答案后合并它们再继续求最小割, 就得到最终答案了.
特别注意几个地方, 网上的好几个Stoer-Wagner版本都存在一些小错误:

1. 算法在做"最大生成树"时更新的不是普通意义上的最大边, 而是与之相连的边的权值和, 当所有边都是单位权值时就是累计度.

2. "最后进入A的两点记为s和t", 网上对s有两种解释, 一是在t之前一个加进去的点, 二是t的前趋节点, 也就是最后选择的那条边的另一端. 正解是第一种!
*/
const int MAXN = 501 , MAXM = 100001 ;
#define typec long long
const typec inf = 1000000000000000LL , maxw = 1000000000000LL ;
typec g[MAXN][MAXN] , dis[MAXN] ;
int used[MAXN] , v[MAXN] ;
int n , m ;
typec mincut( int n )
{
    typec res = inf ;
    for ( int i = 0 ; i < n ; ++i )
		v[i] = i;
	while ( n > 1 )
    {
        used[ v[0] ] = 1 ;
        for ( int i = 1 ; i < n ; ++i )
        {
            used[v[i]] = 0 ;
            dis[v[i]] = g[v[0]][v[i]];
        }
        int last = 0 ;
        for ( int i = 1 ; i < n ; ++i )
        {
            int maxs = -1 ;
            for ( int j = 1 ; j < n ; ++j )
                if ( used[v[j]] == 0 )
                    if ( maxs == -1 || dis[v[j]] > dis[v[maxs]] )
                        maxs = j ;
            used[v[maxs]] = 1 ;
            if ( i == n-1 )
            {
                if ( res > dis[v[maxs]] )
                    res = dis[v[maxs]] ;
                for ( int j = 0 ; j < n ; ++j )
                {
                    g[v[last]][v[j]] += g[v[maxs]][v[j]];
                    g[v[j]][v[last]] += g[v[j]][v[maxs]];
                }
                v[maxs] = v[--n] ;
                break;
            }
            last = maxs ;
            for ( int j = 1 ; j < n ; ++j )
                if ( used[v[j]] == 0 )
                    dis[v[j]] += g[ v[maxs] ][ v[j] ] ;
        }
    }
    return res ;
}

int main()
{
	while ( scanf("%d%d",&n,&m) == 2 )
	{
//		if ( n == 0  && m == 0  )
//			break;
		memset( g , 0 , sizeof g ) ;
		for ( int i = 0 ; i < m ; ++i )
		{
			int sc , sv , vv ;
			scanf("%d%d%d",&sc,&sv,&vv);
//	        --sc , --sv ;
			g[sc][sv] += vv ;
			g[sv][sc] += vv ;
		}
		cout << mincut(n) << '\n' ;
	}
	return 0;
}
