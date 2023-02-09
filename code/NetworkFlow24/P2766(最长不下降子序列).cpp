/*
 * Author:lsty
 * Date:2023.2.7
 * Problem:网络流24题 P2766 最长不下降子序列
 * Tag:网络流
 */
#include <queue>
#include <iostream>
#include <string.h>
#include <algorithm>
#include <stdio.h>

const int N = 505;
int n, a[N];
int height[N];
int ans = -1;

namespace dp{
    void solve(){
        for(int i = 1; i <= n; i++){
            height[i] = 1;
            for(int j = 1; j < i; j++){
                if(a[j] <= a[i]){
                    height[i] = std::max(height[i], height[j] + 1);
                }
            }
            ans = std::max(ans, height[i]);
        }
    } 
}

namespace NetWorkFlow{
    const int N = 1e3 + 10;
    const int M = N * N;
    const int INF = 0x3f3f3f3f;
    int from[M], e[M], ne[M], ori_w[M], w[M], h[N], idx;
    int dep[N], now[N];
    int S;
    int n, m, s, t;
    void add(int u, int v, int c){
        from[idx] = u, e[idx] = v, ne[idx] = h[u], w[idx] = c, ori_w[idx] = w[idx], h[u] = idx++;
        from[idx] = v, e[idx] = u, ne[idx] = h[v], w[idx] = 0, ori_w[idx] = w[idx], h[v] = idx++;
    }

    bool bfs(){
        memset(dep, 0x3f, sizeof dep);
        std::queue<int> q;
        q.push(s);
        dep[s] = 0, now[s] = h[s];
        while(!q.empty()){
            int u = q.front();
            q.pop();

            for(int i = now[u]; ~i; i = ne[i]){
                int v = e[i];
                if(dep[v] == INF && w[i] > 0){
                    q.push(v);
                    dep[v] = dep[u] + 1;
                    now[v] = h[v];
                    if(v == t)
                        return true;
                }
            }
        }
        return false;
    }

    int dfs(int u, int lim){
        if(u == t)
            return lim;
        int flow = 0, k = 0;
        for(int i = now[u]; ~i; i = ne[i]){
            now[u] = i;
            int v = e[i];

            if(w[i] > 0 && dep[v] == dep[u] + 1){
                k = dfs(v, std::min(lim, w[i]));
                w[i] -= k;
                w[i^1] += k;
                flow += k;
                lim -= k;
            }
        }
        return flow;
    }

    int solve(){
        int ans = 0;
        while(bfs())
            ans += dfs(s, INF);
        return ans;
    }

    void init(){
        idx = 0;
        memset(h, -1, sizeof h);
    }

    int prob2(){
        init();
        //总点数 / 源点 / 汇点
        n = 2 * ::n + 2;
        s = 2 * ::n + 1;
        t = 2 * ::n + 2;
        for(int i = 1; i <= ::n; i ++)
            add(i, i + ::n, 1);
        for(int i = 1; i <= ::n; i ++){
            if(height[i] == 1){
                add(s, i, 1);
            }  
            if(height[i] == ::ans){
                add(i + ::n, t, 1);
            }
        }

        for(int i = 1; i <= ::n; i++){
            for(int j = i + 1; j <= ::n; j++){
                if(a[i] <= a[j] && height[i] + 1 == height[j])
                    add(i + ::n, j, 1);
            }
        }
        int tmp = solve();
        return tmp != INF ? tmp : 1;
    }

    int prob3(){
        for(int i = 0; i < idx; i += 2){
            int e1 = i;
            int e2 = i ^ 1;
            w[e1] = ori_w[e1];
            w[e2] = ori_w[e2];
            if(from[e1] == s && e[e1] == 1) w[e1] = INF;
            if(from[e1] == 1 && e[e1] == 1 + ::n)   w[e1] = INF;
            if(from[e1] == ::n + ::n && e[e1] == t) w[e1] = INF;
            if(from[e1] == ::n && e[e1] == ::n + ::n)   w[e1] = INF;
        }
        int tmp = solve();
        return tmp != INF ? tmp : 1;
    }
}

int main(){
    scanf("%d", &n);
    for(int i = 1; i <= n; i++){
        scanf("%d", &a[i]);
    }
    dp::solve();
    printf("%d\n", ans);
    printf("%d\n", NetWorkFlow::prob2());
    printf("%d\n", NetWorkFlow::prob3());
    return 0;
}