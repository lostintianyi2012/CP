#include <iostream>
#include <deque>
#include <stdio.h>
#include <algorithm>
#include <string.h>
#include <vector>

const int N = 1e5 + 10, M = 1e5 + 10, INF = 0x3f3f3f3f;

int n, m, s, t, idx;
int dep[N];
int Flow, Cost;
bool vis[N];

struct Edge {
    int u, v, f, cost;
    Edge(int _u = 0, int _v = 0, int _f = 0, int _cost = 0) {
        u = _u, v = _v, f = _f, cost = _cost;
    }
} edge[M];
std::vector<int> G[N];

void add(int u, int v, int f, int cost) {
    edge[idx++] = Edge(u, v, f, cost);
    edge[idx++] = Edge(v, u, 0, -cost);
    G[u].push_back(idx - 2);
    G[v].push_back(idx - 1);
}

bool SPFA() {
    for (int i = 1; i <= n; i++) {
        dep[i] = INF;
        vis[i] = 0;
    }

    std::deque<int> q;
    q.push_back(t);
    vis[t] = 1;
    dep[t] = 0;

    while (!q.empty()) {
        int u = q.front();
        q.pop_front();
        vis[u] = false;

        //swap
        if (!q.empty() && dep[q.front()] > dep[q.back()])
            std::swap(q.front(), q.back());

        for (int i = 0; i < G[u].size(); i++) {
            //倒着SPFA,为了保证这是反边,要检验正边流量 > 0
            Edge &e = edge[G[u][i] ^ 0];
            Edge &e2 = edge[G[u][i] ^ 1];

            if (e2.f && dep[e.v] > dep[e.u] - e.cost) {
                dep[e.v] = dep[e.u] - e.cost;

                if (!vis[e.v]) {
                    //SLF
                    if (!q.empty() && dep[e.v] > dep[q.front()])
                        q.push_back(e.v);
                    else
                        q.push_front(e.v);

                    vis[e.v] = true;
                }
            }
        }
    }

    return dep[s] < INF;
}

int dfs(int u, int maxflow) {
    vis[u] = 1;

    if (u == t || !maxflow)
        return maxflow;

    int flow = 0, k = 0;

    for (int i = 0; i < G[u].size(); i++) {
        Edge &e = edge[G[u][i] ^ 0];
        Edge &rev = edge[G[u][i] ^ 1];

        if (vis[e.v] || e.f == 0)
            continue;

        if (dep[e.u] - e.cost == dep[e.v]) {
            k = dfs(e.v, std::min(e.f, maxflow));
            e.f -= k;
            rev.f += k;
            Cost += k * e.cost;
            flow += k;
            maxflow -= k;

            if (maxflow == 0)
                break;
        }
    }

    return flow;
}

int main() {
    scanf("%d%d", &n, &m);
    s = 1, t = n;

    for (int i = 1; i <= m; i++) {
        int u, v, f, cost;
        scanf("%d%d%d%d", &u, &v, &f, &cost);
        add(u, v, f, cost);
    }

    while (SPFA()) {
        vis[t] = 1;

        while (vis[t]) {
            for (int i = 1; i <= n; i++)
                vis[i] = 0;

            Flow += dfs(s, INF);
        }
    }

    printf("%d %d\n", Flow, Cost);
    return 0;
}

