/*
 * Author:lsty
 * Date:2023.2.16
 * Problem:NOIP 2021 T2
 * Tag:
 */
#include <bits/stdc++.h>
using namespace std;

#define int long long
const int mod = 998244353;
const int N = 40;
const int M = 110;
inline int read()
{
    int x = 0, f = 1;
    char c = getchar();
    while (!isdigit(c)) {
        if (c == '-')
            f = -1;
        c = getchar();
    }
    while (isdigit(c)) {
        x = (x << 1) + (x << 3) + (c ^ 48);
        c = getchar();
    }
    return x * f;
}

int n, m, i, j, k;
int C[M][M], s[M][M];
int f[M][N][N][N], v[M], K;

int count(int x)
{
    int ans = 0;
    while (x)
        x -= x & -x, ++ans;
    return ans;
}

int dfs(int k, int u, int x, int y)
{
    if (u == n) {
        if (x + count(y) > K)
            return 0;
        return 1;
    }
    if (k > m)
        return 0;
    if (f[k][u][x][y] != -1)
        return f[k][u][x][y];
    int ans = 0;
    for (int i = 0; i <= n - u; ++i) {
        ans = (ans + dfs(k + 1, u + i, x + ((y + i) & 1), (y + i) >> 1) * s[k][i] % mod * C[u + i][i] % mod) % mod;
    }
    f[k][u][x][y] = ans;
    return f[k][u][x][y];
}

signed main()
{
    memset(f, -1, sizeof(f));
    n = read();
    m = read();
    K = read();
    for (i = 0; i <= m; ++i)
        v[i] = read();
    C[0][0] = 1;
    for (i = 1; i <= n; ++i)
        for (j = C[i][0] = 1; j <= i; ++j)
            C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % mod;
    for (i = 0; i <= m; ++i) {
        s[i][0] = 1;
        for (j = 1; j <= n; ++j)
            s[i][j] = (s[i][j - 1] * v[i]) % mod;
    }
    printf("%lld\n", dfs(0, 0, 0, 0));
    return 0;
}