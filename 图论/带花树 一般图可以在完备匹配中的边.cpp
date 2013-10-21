const int maxn=150;
int Link[maxn][maxn];
int n,m;
int match[maxn];
int Queue[maxn],head,tail;
int pred[maxn],base[maxn];
bool InQueue[maxn],InBlossom[maxn];
int start,finish;
int newbase;

inline void push(int u){
	Queue[tail++]=u;InQueue[u]=true;
}
inline int pop(){
	return Queue[head++];
}
inline int FindCommonAncestor(int u,int v){
	static bool InPath[maxn];
	for(int i=0;i<n;++i) InPath[i]=0;
	while(1)
	{
		u=base[u];
		InPath[u]=true;
		if(u==start) break;
		u=pred[match[u]];
	}
	while(1)
	{
		v=base[v];
		if(InPath[v]) break;
		v=pred[match[v]];
	}
	return v;
}
inline void ResetTrace(int u){
	int v;
	while(base[u]!=newbase){
		v=match[u];
		InBlossom[base[u]]=InBlossom[base[v]]=true;
		u=pred[v];
		if(base[u]!=newbase) pred[u]=v;
	}
}
inline void BlossomConstract(int u,int v){
	newbase=FindCommonAncestor(u,v);
	for(int i=0;i<n;++i) InBlossom[i]=0;
	ResetTrace(u),ResetTrace(v);
	if(base[u]!=newbase) pred[u]=v;
	if(base[v]!=newbase) pred[v]=u;
	for(int i=0;i<n;++i) if(InBlossom[base[i]])
	{
		base[i]=newbase;
		if(!InQueue[i]) push(i);
	}
}
inline bool FindAugmentingPath(int u){
	bool found=false;
	for(int i=0;i<n;++i) pred[i]=-1,base[i]=i;
	for(int i=0;i<n;++i) InQueue[i]=0;
	start=u;finish=-1;
	head=tail=0;
	push(start);
	while(head<tail){
		int u=pop();
		for(int i=n-1;i>=0;i--) if(Link[u][i]){
			int v=i;
			if(base[u]!=base[v]&&match[u]!=v)
			{
				if(v==start||(match[v]>=0&&pred[match[v]]>=0))
				{
					BlossomConstract(u,v);
				}
				else if(pred[v]==-1)
				{
					pred[v]=u;
					if(match[v]>=0) push(match[v]);
					else
					{
						finish=v;
						return true;
					}
				}
			}
		}
	}
	return found;
}
inline void AugmentPath(){
	int u,v,w;
	u=finish;
	while(u>=0)
	{
		v=pred[u];
		w=match[v];
		match[v]=u;
		match[u]=v;
		u=w;
	}
}
void FindMaxMatching(){
	for(int i=0;i<n;++i) match[i]=-1;
	for(int i=0;i<n;++i) if(match[i]==-1)
	{
		if(FindAugmentingPath(i)) AugmentPath();
	}
}

int recorde[maxn*maxn][3];
int copymatch[maxn];
int copyedge[maxn][maxn];

int main() {
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;++i){
		int x,y;
		scanf("%d%d",&x,&y);
		--x,--y;
		recorde[i][0]=x,recorde[i][1]=y;
		if(x!=y) ++Link[x][y],++Link[y][x];
	}
	FindMaxMatching();
	int nowmatch=0;
	for(int i=0;i<n;++i) nowmatch+=match[i]!=-1;
	for(int i=0;i<n;++i)
	{
		copymatch[i]=match[i];
	}
	for(int i=0;i<n;++i) for(int j=0;j<n;++j) copyedge[i][j]=Link[i][j];
	if(nowmatch!=n){
		while(m--) printf("NO\n");
	}
	else
	{
		for(int edgenum=1;edgenum<=m;++edgenum){
			int x=recorde[edgenum][0],y=recorde[edgenum][1];
			if(x==y){printf("NO\n");continue;}
			if(match[x]==y)
			{
				printf("YES\n");
			}
			else
			{
				for(int i=0;i<n;++i) Link[x][i]=Link[i][x]=Link[i][y]=Link[y][i]=0;
				match[match[x]]=-1,match[match[y]]=-1;
				printf("%s\n",FindAugmentingPath(match[x])?"YES":"NO");
				for(int i=0;i<n;++i) match[i]=copymatch[i];
				for(int i=0;i<n;++i)
				{
					Link[i][x]=Link[x][i]=copyedge[x][i];
					Link[i][y]=Link[y][i]=copyedge[y][i];
				}
			}
		}
	}
	return 0;
}
