/*
 * Author:lostintianyi
 * Date:2023.1.14
 * Problem:template
 */
#include <bits/stdc++.h>

using namespace std;
const int N = 250, M = 1e4 + 1000;
const long long INF = 0x3f3f3f3f;

int n, m, s, t;
int idx = 0, h[N], e[M], ne[M];
long long w[M];

inline void add(int a, int b, long long c){
    e[idx] = b, ne[idx] = h[a], w[idx] = c, h[a] = idx++;
}

int now[N], dep[N];

bool bfs(){
    memset(dep, 0x3f, sizeof dep);

    dep[s] = 0;
    now[s] = h[s];

    queue<int> Q;
    Q.push(s);

    while (!Q.empty()) {
        int u = Q.front();
        Q.pop();

        for (int i = h[u]; ~i; i = ne[i]) {
            int v = e[i];
            //当前弧优化
            if (w[i] > 0 && dep[v] == INF) {
                Q.push(v);
                now[v] = h[v];
                dep[v] = dep[u] + 1;
                if (v == t)
                    return true;
            }
        }
    }
    return false;
}

int dfs(int u, long long maxflow){
    if (u == t)
        return maxflow;

    long long k = 0, flow = 0;
    for (int i = now[u]; ~i && maxflow > 0; i = ne[i]) {
        now[u] = i;
        int v = e[i];

        if (w[i] > 0 && (dep[v] == dep[u] + 1)) {
            k = dfs(v, min(maxflow, (long long)w[i]));
            if (k == 0)
                dep[v] = INF;
            w[i] -= k;
            w[i ^ 1] += k;
            flow += k;
            maxflow -= k;
        }
    }
    return flow;
}

int main()
{
    memset(h, -1, sizeof h);
    scanf("%d%d%d%d", &n, &m, &s, &t);

    for (int i = 1; i <= m; i++) {
        int a, b;
        long long c;
        scanf("%d%d%lld", &a, &b, &c);
        add(a, b, c), add(b, a, 0);
    }

    long long ans = 0;
    while (bfs()) {
        ans += dfs(s, INF);
    }
    printf("%lld\n", ans);

    return 0;
}