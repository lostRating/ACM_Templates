#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <string>
#include <bitset>

typedef long long LL;
#define pb push_back
#define MPII make_pair<int, int>
#define PII pair<int, int>
#define sz(x) (int)x.size()

using namespace std;

template<class T> T abs(T x){if (x < 0) return -x; else return x;}

const int maxn = 500000;
int head[maxn], stack[maxn], dfn[maxn], low[maxn], visit[maxn], tt[maxn];
int n, m, num, top, Time;
bool cactus;

struct Edge{
	int x, next;
}gragh[maxn];

void Add_edge(int x, int y){
	gragh[++num].x = y;
	gragh[num].next = head[x];
	head[x] = num;
}

void Dfs(int u){
	++Time;
	dfn[u] = low[u] = Time;
	visit[u] = 1;
	stack[++top] = u;
	for (int i = head[u]; i != 0; i = gragh[i].next){
		if (visit[gragh[i].x] == 2) cactus = false;                           //character 1
		if (visit[gragh[i].x] == 0){
			Dfs(gragh[i].x);
			if (low[gragh[i].x] > dfn[u]) cactus = false;					  //character 2
			if (low[gragh[i].x] < dfn[u]){
				++tt[u];
				if (low[gragh[i].x] < low[u]) low[u] = low[gragh[i].x];
			}
		} else if (low[gragh[i].x] < dfn[u]){
			++tt[u];
			if (low[gragh[i].x] < low[u]) low[u] = low[gragh[i].x];
		}
		if (tt[u] > 1) cactus = false;										//character 3
	}
	visit[u] = 2;
}

int main(){
	int Cases;
	scanf("%d", &Cases);
	for (; Cases; --Cases){
		scanf("%d", &n);
		int x, y;
		scanf("%d%d", &x, &y);
		num = 0;
		top = 0;
		Time = 0;
		for (int i = 1; i <= n + 1; ++i){
			head[i] = low[i] = dfn[i] = visit[i] = stack[i] = tt[i] = 0;
		}
		while (x != 0 || y != 0){
			Add_edge(x + 1, y + 1);
			scanf("%d%d", &x, &y);
		}
		bool ff = true;
		cactus = true;
		for (int i = 1; i <= n; ++i)
			if (!visit[i]){
				if (!ff){
					cactus = false;
				}
				Dfs(i);
				ff = false;
			}
		if (cactus) puts("YES"); else puts("NO");
	}
	return 0;
}

