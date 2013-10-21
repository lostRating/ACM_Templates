#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
using namespace std;
 
const int maxn=400100;
char str[maxn];
int n,y[maxn],sum[maxn],height[maxn],c[maxn],sa[maxn],rk[maxn];
 
void swap(int a[maxn],int b[maxn]){
     for (int i=0;i<n;i++){
         int t=a[i];a[i]=b[i];b[i]=t;
     }
}
 
int main(){
    memset(sum, 0, sizeof(sum));
	memset(rk, 0, sizeof(rk));
	memset(sa, 0, sizeof(sa));
	for (int i = 0; i < N; ++i) ++sum[c[i]];
	for (int i = 1; i < n + 30; ++i) sum[i] += sum[i - 1];
	for (int i = 0; i < N; ++i) sa[--sum[c[i]]] = i;
	int p = 1;
	rk[sa[0]] = 1;
	for (int i = 1; i < N; ++i){
		if (c[sa[i]] != c[sa[i - 1]]) ++p;
		rk[sa[i]] = p;
	}

	for (int j = 1; j < N; j <<= 1){
		p = 0;
		for (int i = N - j; i < N; ++i) y[p++] = i;
		for (int i = 0; i < N; ++i) if (sa[i] >= j) y[p++] = sa[i] - j;
		for (int i = 0; i <= N; ++i) sum[i] = 0;
		for (int i = 0; i < N; ++i) ++sum[rk[y[i]]];
		for (int i = 1; i <= N; ++i) sum[i] += sum[i - 1];
		for (int i = N - 1; i >= 0; --i) sa[--sum[rk[y[i]]]] = y[i];
		swap(rk, y);
		p = 1;
		rk[sa[0]] = 1;
		for (int i = 1; i < N; ++i){
			if (y[sa[i]] != y[sa[i - 1]] || y[sa[i] + j] != y[sa[i - 1] + j]) ++p;
			rk[sa[i]] = p;
		}
	}
// height[i] 表示sa[i]与sa[i + 1]的最长公共前缀
	int j = 0;
	memset(height, 0, sizeof(height));
	for (int i = 0; i < N; ++i)
		if (rk[i] != 1){
			int k = sa[rk[i] - 2];
			while (i + j < N && k + j < N && c[i + j].w == c[k + j].w) ++j;
			height[rk[i] - 2] = j;
			if (j > 0) --j;
		}

    return 0;
}
