#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cstdlib>
#include <string>
#include <set>
#include <map>
#include <queue>
#include <vector>
#include <cmath>

typedef long long LL;
#define pb push_back
using namespace std;

template<class T> T abs(T x){if (x < 0) return -x; else return x;}

const LL inf = 1ll << 62;
const int maxn = 101000;
int T, n, Index;
LL res;

struct Point{
    int c[2];
    bool operator < (const Point&u)const{
        return c[Index] < u.c[Index];
    }
}c[maxn], bak[maxn];

LL dist(Point u, Point v){
    return (LL)(u.c[0] - v.c[0]) * (LL)(u.c[0] - v.c[0]) + (LL)(u.c[1] - v.c[1]) * (LL)(u.c[1] - v.c[1]);
}

struct KdTree{
    Point p;
    int minc[2], maxc[2];

    void init(Point u){
        for (int i = 0; i < 2; ++i)
            minc[i] = maxc[i] = u.c[i];
    }

    void merge(KdTree u){
        for (int i = 0; i < 2; ++i){
            minc[i] = min(minc[i], u.minc[i]);
            maxc[i] = max(maxc[i], u.maxc[i]);
        }
    }

    LL dist(Point p){
        LL tmp = 0;
        for (int i = 0; i < 2; ++i)
            if (p.c[i] < minc[i]) tmp += (LL)(minc[i] - p.c[i]) * (LL)(minc[i] - p.c[i]); else 
                if (p.c[i] > maxc[i]) tmp += (LL)(p.c[i] - maxc[i]) * (LL)(p.c[i] - maxc[i]);
        return tmp;
    }
}Kdt[4 * maxn];

void Construct(int t, int l, int r, int dep){
    int mid = (l + r) >> 1;
    Index = dep % 2;
    nth_element(c + l + 1, c + mid + 1, c + r + 1);
    Kdt[t].p = c[mid];
    Kdt[t].init(c[mid]);
    if (l == r) return;
    Construct(t * 2, l, mid, dep + 1);
    Construct(t * 2 + 1, mid + 1, r, dep + 1);
    Kdt[t].merge(Kdt[t * 2]);
    Kdt[t].merge(Kdt[t * 2 + 1]);
}

void Query(int t, int l, int r, int dep, Point p){
    int mid = (l + r) / 2;
    if (Kdt[t].dist(p) >= res) return;
    LL dt = dist(p, Kdt[t].p);
    if (dt > 0 && dt < res) res = dt;
    if (l == r) return;
    Index = dep % 2;
    if (p < Kdt[t].p){
        Query(2 * t, l, mid, dep + 1, p);
        Query(2 * t + 1, mid + 1, r, dep + 1, p);
    } else {
        Query(2 * t + 1, mid + 1, r, dep + 1, p);
        Query(2 * t, l, mid, dep + 1, p);
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin >> T;
    for (; T; --T){
        cin >> n;
        for (int i = 1; i <= n; ++i){
            cin >> c[i].c[0] >> c[i].c[1];
            bak[i] = c[i];
        }
        Construct(1, 1, n, 0);
        for (int i = 1; i <= n; ++i){
            res = inf;
            Query(1, 1, n, 0, bak[i]);
            cout << res << endl;
        }
    }
    return 0;
}

