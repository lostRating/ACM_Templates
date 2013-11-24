#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
#include<fstream>
#include<map>
#include<ctime>
#include<set>
#include<queue>
#include<cmath>
#include<vector>
#include<bitset>
#include<functional>
#define x first
#define y second
#define mp make_pair
#define pb push_back
using namespace std;

typedef long long LL;
typedef double ld;

const int MAX=100000+10;
const int INF=2000000000;
const int NUM=20;

int n,m,Q;
pair<int,int> ask[MAX];
LL ans[MAX];

struct Edge
{
    int x,y,z,num;
}e[NUM][MAX],ed[MAX];
int nume[NUM],fa[MAX],place[MAX],old[MAX];

int findfather(int u)
{
    return fa[u]==u?u:fa[u]=findfather(fa[u]);
}

int operator < (const Edge& a,const Edge& b)
{
    return a.z<b.z;
}

int temp[MAX];
LL tot=0;

void work(int dep,int l,int r,LL now)
{
    if(l>r)return;
    int i,mid=(l+r)/2,m=nume[dep];
    if(l==r)old[ask[l].x]=ask[l].y;
    for(i=1;i<=m;++i)
    {
        e[dep][i].z=old[e[dep][i].num];
        ed[i]=e[dep][i];
    }
    if(l==r)
    {
        ans[l]=now;
        for(i=1;i<=m;++i)
            fa[ed[i].x]=ed[i].x,fa[ed[i].y]=ed[i].y;
        sort(ed+1,ed+m+1);
        for(i=1;i<=m;++i)
        {
            int a=findfather(ed[i].x),b=findfather(ed[i].y);
            if(a!=b)
                ans[l]+=ed[i].z,fa[a]=b;
        }
        return;
    }
    for(i=1;i<=m;++i)
    {
        place[ed[i].num]=i;
        fa[ed[i].x]=ed[i].x,fa[ed[i].y]=ed[i].y;
    }
    for(i=l;i<=r;++i)
        ed[place[ask[i].x]].z=-INF;
    sort(ed+1,ed+m+1);
    temp[0]=0;
    for(i=1;i<=m;++i)
    {
        int a=findfather(ed[i].x),b=findfather(ed[i].y);
        if(a!=b)temp[++temp[0]]=i,fa[a]=b;
    }
    for(i=1;i<=m;++i)
        fa[ed[i].x]=ed[i].x,fa[ed[i].y]=ed[i].y;
    for(i=1;i<=temp[0];++i)
    {
        int p=temp[i];
        if(ed[p].z==-INF)continue;
        now+=ed[p].z;
        fa[findfather(ed[p].x)]=findfather(ed[p].y);
    }
    for(i=1;i<=m;++i)
    {
        ed[i].x=findfather(ed[i].x),ed[i].y=findfather(ed[i].y);
        if(ed[i].z==-INF)ed[i].z=INF;
    }
    sort(ed+1,ed+m+1);
    nume[dep+1]=0;
    for(i=1;i<=m;++i)
    {
        int a=findfather(ed[i].x),b=findfather(ed[i].y);
        if(a!=b)
        {
            fa[a]=b;
            if(ed[i].z!=INF)e[dep+1][++nume[dep+1]]=ed[i];
        }
    }
    for(i=1;i<=m;++i)
        if(ed[i].z==INF)
            e[dep+1][++nume[dep+1]]=ed[i];
    work(dep+1,l,mid,now);
    work(dep+1,mid+1,r,now);
    return;
}

int main()
{
    int i;
    scanf("%d%d%d",&n,&m,&Q);
    nume[0]=m;
    for(i=1;i<=m;++i)
    {
        scanf("%d%d%d",&e[0][i].x,&e[0][i].y,&e[0][i].z);
        e[0][i].num=i;
        old[i]=e[0][i].z;
    }
    for(i=1;i<=Q;++i)
        scanf("%d%d",&ask[i].x,&ask[i].y);
    work(0,1,Q,0);
    for(i=1;i<=Q;++i)
        printf("%lld\n",ans[i]);
    return 0;
}
