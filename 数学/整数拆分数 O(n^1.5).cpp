#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 100001, MOD = 1000000007;
int ans[N];

int main() {
    ans[0] = 1;
    for (int i = 1; i < N; ++i) {
        ans[i] = 0;
        for (int j = 1; j * (3 * j - 1) / 2 <= i; ++j) {
            (ans[i] += (j % 2 ? 1 : -1) * ans[i - j * (3 * j - 1) / 2]) %= MOD;
        }
        for (int j = -1; j * (3 * j - 1) / 2 <= i; --j) {
            (ans[i] += (j % 2 ? 1 : -1) * ans[i - j * (3 * j - 1) / 2]) %= MOD;
        }
        if (ans[i] < 0) {
            ans[i] += MOD;
        }
    }
    int t;
    scanf("%d", &t);
    while (t--) {
        int n;
        scanf("%d", &n);
        printf("%d\n", ans[n]);
    }
    return 0;
}