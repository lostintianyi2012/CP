#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <string.h>
#include <vector>

const int N = 5e3 + 10;
std::vector<int> G[N];
int n, m;

namespace situation1{
    int vis[N];
    
    void dfs(int u){
        vis[u] = true;
        printf("%d ", u);
        for(auto edge : G[u]){
            if(vis[edge])
                continue;
            dfs(edge);
        }
    }
}

namespace situation2{
    std::vector<std::pair<int, int>> a;
    int banu, banv;
    bool vis[N];
    int ans[N], idx;
    int t[N];

    bool chk(int u, int v){
        if((u == banu && v == banv) || (v == banu && u == banv))
            return false;
        return true;
    }

    void dfs(int u){
        vis[u] = true;
        t[++idx] = u;
        for(auto edge : G[u]){
            if(vis[edge] || !chk(edge, u))
                continue;
            dfs(edge);
        }
    }

    void new_ans(){
        for(int i = 1; i <= n; i++)
            if(!t[i])
                return ;
        int i;
        for(i = 1; i <= n && ans[i] == t[i]; i++);
        if(t[i] > ans[i])
            return ;
        if(t[i] < ans[i]){
            for(; i <= n; i++)
            ans[i] = t[i];
        }
    }
}

int main(){
    freopen("travel.in", "r", stdin);
    freopen("travel.out", "w", stdout);
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= m; i++){
        int u, v;
        scanf("%d%d", &u, &v);
        G[u].push_back(v);
        G[v].push_back(u);
        situation2::a.push_back(std::make_pair(u, v));
    }
    for(int i = 1; i <= n; i++){
        std::sort(G[i].begin(), G[i].end());
    }
    if(m == n-1){
        situation1::dfs(1);
    }
    if(m == n){ 
        memset(situation2::ans, 0x3f, sizeof situation2::ans);
        for(auto x : situation2::a){
            situation2::idx = 0;
            memset(situation2::vis, 0, sizeof situation2::vis);
            situation2::banu = x.first, situation2::banv = x.second;
            situation2::dfs(1);
            situation2::new_ans();
        }
        for(int i = 1; i <= n; i++){
            printf("%d ", situation2::ans[i]);
        }
    }
    return 0;
}