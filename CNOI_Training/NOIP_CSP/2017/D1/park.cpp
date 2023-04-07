/*
 * Author:lsty
 * Date:2023.2.6
 * Problem:NOIP 2017 D1T3 逛公园
 * Tag:最短路 DP 
 */
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string.h>
#include <queue>

const int N = 1e5 + 10, M = 2e5 + 10, K = 52;
int h[N], e[M], ne[M], w[M], idx;
int h2[N], e2[M], ne2[M], w2[M], idx2;
int n, m, k, p;
bool st[N];
int dis[N];
long long f[K][N];
bool InStack[K][N];
bool flag = 0;

void init(){
    memset(h, -1, sizeof h);
    memset(f, 0, sizeof f);
    memset(h2, -1, sizeof h2);
    memset(InStack, 0, sizeof InStack);
    idx = 0, flag = 0, idx2 = 0;
}

void add(int u, int v, int c){
    e[idx] = v, ne[idx] = h[u], w[idx] = c, h[u] = idx++;
} 

void add2(int u, int v, int c){
    e2[idx2] = v, ne2[idx2] = h2[u], w2[idx2] = c, h2[u] = idx2++;
} 

void dijkstra(){
    memset(dis, 0x3f, sizeof dis);
    memset(st, 0, sizeof st);
    std::priority_queue<std::pair<int, int> , std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> heap;
    heap.push({0, 1});
    dis[1] = 0;

    while(!heap.empty()){
        std::pair<int, int> now = heap.top();
        heap.pop();

        int u = now.second, d = now.first;
        if(st[u])
            continue;
        st[u] = true;
        for(int i = h[u]; ~i; i = ne[i]){
            int v = e[i];
            if(dis[v] > d + w[i]){
                dis[v] = d + w[i];
                heap.push({dis[v], v});
            }
        }
    }
}

int dfs(int u, int k){
    if(k < 0)
        return 0;
    if(InStack[k][u]){
        flag = 1;
        return 0;
    }
    if(f[k][u])
        return f[k][u];
    InStack[k][u] = 1;
    long long ans = 0;

    for(int i = h2[u]; ~i; i = ne2[i]){
        int v = e2[i];
        ans = (ans + dfs(v, dis[u] - dis[v] + k - w2[i])) % p;
        if(flag)
            return 0;
    }
    InStack[k][u] = 0;
    return f[k][u] = ans;
}

int main(){
    int T;
    scanf("%d", &T);
    while(T--){
        init();
        scanf("%d%d%d%d", &n, &m, &k, &p);
        for(int i = 0; i < m; i++){
            int a, b, c;
            scanf("%d%d%d", &a, &b, &c);
            add(a, b, c);
            add2(b, a, c);
        }
        dijkstra();
        //printf("%d\n", dis[n]);

        dfs(1, 0);
        f[0][1] = 1;
        long long ans = 0;
        for(int i = 0; i <= k; i++){
            ans = (ans + dfs(n, i)) % p;
        }
        if(flag)    puts("-1");
        else        printf("%lld\n", ans);
    }
    return 0;
}