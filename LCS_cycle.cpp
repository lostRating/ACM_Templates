#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<climits>

const int N = 1005 << 1;
int n, a[N], b[N];

bool has(int i, int j) {
    return a[(i - 1) % n] == b[(j - 1) % n];
}

const int DELTA[3][2] = {{0, -1}, {-1, -1}, {-1, 0}};

int from[N][N];

int solve() {
    memset(from, 0, sizeof(from));
    int ret = 0;
    for (int i = 1; i <= 2 * n; ++i) {
        from[i][0] = 2;
        int left = 0;
        int up = 0;
        for (int j = 1; j <= n; ++j) {
            int upleft = up;
            if (!has(i, j)) {
                upleft = INT_MIN;
            } else {
                upleft++;
            }
            if (from[i - 1][j]) {
                up++;
            }
            int max = std::max(left, std::max(upleft, up));
            if (left == max) {
                from[i][j] = 0;
            } else if (upleft == max) {
                from[i][j] = 1;
            } else {
                from[i][j] = 2;
            }
            left = max;
        }
        if (i >= n) {
            int count = 0;
            for (int x = i, y = n; y;) {
                int t = from[x][y];
                count += t == 1;
                x += DELTA[t][0];
                y += DELTA[t][1];
            }
            ret = std::max(ret, count);
            int x = i - n + 1;
            from[x][0] = 0;
            int y = 0;
            while (y <= n && from[x][y] == 0) {
                y++;
            }
            for (; x <= i; ++x) {
                from[x][y] = 0;
                if (x == i) {
                    break;
                }
                for (; y <= n; ++y) {
                    if (from[x + 1][y] == 2) {
                        break;
                    }
                    if (y + 1 <= n && from[x + 1][y + 1] == 1) {
                        y++;
                        break;
                    }
                }
            }
        }
    }
    return ret;
}

int main() {
    while (scanf("%d", &n) == 1 && n) {
        for (int i = 0; i < n; ++i) scanf("%d", a + i);
        for (int i = 0; i < n; ++i)	scanf("%d", b + i);
        printf("%d\n", solve());
    }
    return 0;
}
