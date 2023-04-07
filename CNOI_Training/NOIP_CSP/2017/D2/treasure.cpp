/*
 * Author:lsty
 * Date:2023.2.6
 * Problem:NOIP 2017 D2T2 宝藏
 * Tag:状压DP
 */
#include <algorithm>
#include <cstdio>
#include <iostream>
#include <string.h>
#include <vector>

// 考虑 f[j][2^{i-1} | s][dep] 表示第 j 个点在点集 s 中深度为 dep 时的最小值
const int N = 13;
int fullset;
int g[N][N];
int n, m;
int f[N][1 << N][N];
int d[N];
int ans;

void dfs(int s, int sum, int dep)
{
    if (sum >= ans)
        return;
    if (s == fullset) {
        ans = sum;
        return;
    }
    for (int i = 1; i <= n; i++) {
        if (!(1 << (i - 1) & s))
            continue;
        for (int j = 1; j <= n; j++) {
            if (!(1 << (j - 1) & s) && g[i][j] < 0x3f3f3f3f) {
				if(f[j][1 << (j - 1) | s][dep+1] <= sum + d[i] * g[i][j])
					continue;
                int k = 1 << (j - 1) | s;
                f[j][k][dep + 1] = sum + d[i] * g[i][j];
                d[j] = d[i] + 1;
                dfs(k, f[j][k][dep + 1], dep + 1);
            }
        }
    }
}

int main()
{
    memset(g, 0x3f, sizeof g);
    scanf("%d%d", &n, &m);
    fullset = (1 << n) - 1;
    for (int i = 1; i <= m; i++) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        g[u][v] = g[v][u] = std::min(g[u][v], w);
    }

    ans = 0x3f3f3f3f;
    for (int i = 1; i <= n; i++) {
        memset(f, 0x3f, sizeof f);
        memset(d, 0, sizeof d);
        d[i] = 1, dfs(1 << (i - 1), 0, 0);
    }
    printf("%d\n", ans);
    return 0;
}