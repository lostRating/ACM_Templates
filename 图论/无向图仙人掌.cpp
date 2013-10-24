#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <map>
#include <set>
#include <queue>
#include <deque>
#include <ctime>
#include <sstream>
#include <fstream>
#include <bitset>
 
using namespace std;
 
typedef long long LL;
typedef long double real;
 
#define mp make_pair
#define pb push_back
#define sz(X) ((int)((X).size()))
 
const double eps = 1e-16;
const int lim = 1000000000;

const int maxn = 50000, maxm = 3000000, mo = 10000;
bool cactus;
int head[maxn], father[maxn], dep[maxn];
int x[maxn], y[maxn];
int ans[maxn], num, n, len, m;
bool visit[maxn];

struct Edge{
	int x, next;
}gragh[maxm];

void Add_edge(int x, int y){
	gragh[++num].x = y;
	gragh[num].next = head[x];
	head[x] = num;
}


void Dfs(int u){
	visit[u] = true;
	for (int i = head[u]; i; i = gragh[i].next)
		if (!visit[gragh[i].x]){
			father[gragh[i].x] = u;
			dep[gragh[i].x] = dep[u] + 1;
			Dfs(gragh[i].x);
		}
}

void Mul(int k){
	int g = 0;
	for (int i = 1; i <= len; ++i){
		int t = ((LL)ans[i] * (LL)k + g) / mo;
		ans[i] = ((LL)ans[i] * (LL)k + g) % mo;
		g = t;
	}
	if (g > 0) ans[++len] = g;
}

void Update(int u, int v){
	int tmp = 1;
	while (u != v){
		if (dep[u] < dep[v]) swap(u, v);
		if (visit[u]) cactus = false;
		visit[u] = true;
		u = father[u];
		++tmp;
	}
	Mul(tmp + 1);
}

void Print(){
	printf("%d", ans[len]);
	for (int i = len - 1; i; --i){
		if (ans[i] / 1000 == 0) putchar('0');
		if (ans[i] / 100 == 0) putchar('0');
		if (ans[i] / 10 == 0) putchar('0');
		printf("%d", ans[i]);
	}
	printf("\n");
}

int main(){
	scanf("%d%d", &n, &m);
	num = 0;
	memset(head, 0, sizeof(head));
	memset(visit, false, sizeof(visit));
	memset(father ,0, sizeof(father));
	int N = 0;
	for (int i = 0; i < m; ++i){
		int k;
		scanf("%d", &k);
		int pre = 0;
		for (int j = 0; j < k ; ++j){
			int t;
			scanf("%d", &t);
			if (pre){
				x[++N] = pre;
				y[N] = t;
				Add_edge(pre, t);
				Add_edge(t, pre);
			}
			pre = t;
		}
	}
	memset(dep, 0, sizeof(dep));
	Dfs(1);
	for (int i = 1; i <= n; ++i)
		if (!visit[i]){
			puts("0");
			return 0;
		}
	cactus = true;
	memset(visit, false, sizeof(visit));
	len = 1;
	ans[1] = 1;
	for (int i = 1; i <= N; ++i)
		if (father[x[i]] != y[i] && father[y[i]] != x[i]){
			Update(x[i], y[i]);
			if (!cactus) break;
		}
	if (!cactus) puts("0"); else {
		Print();
	}
	return 0;
}
