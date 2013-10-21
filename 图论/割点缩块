#include<vector> 
#include<cstdio>
#include<cstring>

using namespace std;

const int maxn = 100000+5;
const int maxm = 200000+5;
int e[maxm],prev[maxm];
int info[maxn]; 
int dfn[maxn],low[maxn],stack[maxn];
vector<int> Block[maxn];
int cntB,cnt,top,tote;

void insertE( int x,int y ){
	++tote;
	e[tote]=y;
	prev[tote]=info[x];
	info[x]=tote;
}

void Min( int &x,int y ) { if(y < x) x = y; } 

void Dfs( int x,int father){
	dfn[x] = low[x] = ++cnt;
	stack[++top] = x;
	for(int t=info[x];t;t=prev[t])
		if(dfn[e[t]] == 0){ 
			int tmp = top;
			Dfs(e[t],x);
			Min(low[x],low[e[t]]);
			if(low[e[t]] >= dfn[x]) {
				Block[++cntB].clear();
				for(int k=tmp+1;k<=top;++k) Block[cntB].push_back(stack[k]);
				Block[cntB].push_back(x); top=tmp;
			}
		} else if(e[t]!=father) Min(low[x],dfn[e[t]]); 
}

int main() {
	int n,m;
	scanf("%d%d",&n,&m); 
	memset(info,0,sizeof(info)); 
	tote=0;
	for(int i=0;i<m;++i) { 
		int x,y;
		scanf("%d%d",&x,&y);
		insertE(x,y);
		insertE(y,x);
	}
	memset(dfn,0,sizeof(dfn));
	cnt=top=cntB=0;
	for(int i=1;i<=n;++i)
		if(dfn[i] == 0) Dfs(i,-1);
	printf("%d\n",cntB);
	for(int i=1;i<=cntB;++i) {
		for(int j=0;j<Block[i].size();++j)
			printf("%d ",Block[i][j]); puts("");
	}
	return 0;
}
