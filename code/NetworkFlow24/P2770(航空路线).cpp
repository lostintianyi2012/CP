/*
 * Author:lsty
 * Date:2023.2.7
 * Problem:网络流24题 P2770 航空路线
 * Tag:网络流
 */
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string.h>
#include <map>
#include <vector>
#include <deque>

int n, m, idx;
std::map<std::string, int> city;
std::map<int, std::string> node;

namespace zkw{
    const int N = 210;
    const int M = N * N, INF = 0x3f3f3f3f;
    int n, m, s, t;
    int dep[N];
    int MaxFlow = 0, MinCost = 0;
    bool vis[N];

    struct Edge{
        int u, v, f, c;
        Edge(int _u = 0, int _v = 0, int _f = 0, int _c = 0){
            u = _u, v = _v, f = _f, c = _c;
        }
    }edge[M];

    std::vector<int> G[N];
    int idx;

    void add(int u, int v, int f, int c){
        edge[idx++] = Edge{u, v, f, c};
        edge[idx++] = Edge{v, u, 0, -c};
        G[u].push_back(idx-2);
        G[v].push_back(idx-1);
    }

    bool SPFA(){
        memset(dep, 0x3f, sizeof dep);
        memset(vis, 0, sizeof vis);
        std::deque<int> q;
        q.push_back(t);
        vis[t] = 1;
        dep[t] = 0;

        while(!q.empty()){
            int u = q.front();
            q.pop_front();
            vis[u] = false;

            if(!q.empty() && dep[q.front()] > dep[q.back()]){
                std::swap(q.front(), q.back());
            }

            for(int i : G[u]){
                Edge& e = edge[i];
                Edge& rev = edge[i^1];
                
                if(rev.f && dep[e.v] > dep[e.u] - e.c){
                    dep[e.v] = dep[e.u] - e.c;

                    if(!vis[e.v]){
                        vis[e.v] = true;
                        if(!q.empty() && dep[e.v] < dep[q.front()])
                            q.push_front(e.v);
                        else
                            q.push_back(e.v);
                    }
                }
            }
        }
        return dep[s] < INF;
    }

    int MCMF(int u, int maxflow){
        vis[u] = true;
        if(u == t || !maxflow)
            return maxflow;

        int flow = 0, k = 0;
        for(int i : G[u]){
            Edge& e1 = edge[i];
            Edge& e2 = edge[i^1];
            
            if(vis[e1.v] || !e1.f)
                continue;
            if(dep[e1.v] == dep[e1.u] - e1.c){
                k = MCMF(e1.v, std::min(maxflow, e1.f));
                e1.f -= k;
                e2.f += k;
                MinCost += e1.c * k;
                flow += k;
                maxflow -= k;
                if(!maxflow)
                    break;
            }
        }
        return flow;
    }

    void work(){
        n = ::n + ::n;
        s = 1;
        t = n;
        while(SPFA()){
            vis[t] = true;
            while(vis[t]){
                memset(vis, 0, sizeof vis);
                MaxFlow += MCMF(s, INF);
            }
        }
        //减去源点和汇点多贡献的一个
        MinCost = (-MinCost) - 2;
    }
}

bool vis[zkw::N];
std::vector<int> G[zkw::N];

void dfs(int u){
    if(!vis[u]){
        vis[u] = true;
        std::cout << node[u] << std::endl;
        for(int i : G[u])
            dfs(i);
    }
}

int main(){
//    freopen("airl.in", "r", stdin);
//    freopen("airl.out", "w", stdout);
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; i++){
        std::string a;
        std::cin >> a;
        city[a] = ++idx;
        node[idx] = a;
        if(idx == 1 || idx == n)
            zkw::add(idx, idx + n, 2, -1);
        else
            zkw::add(idx, idx + n, 1, -1);
    }
    for(int i = 1; i <= m; i++){
        std::string a, b;
        std::cin >> a >> b;
        int x = city[a], y = city[b];
        if(x > y)
            std::swap(x, y);
        //连接几个不同城市
        zkw::add(x + n, y, zkw::INF, 0);
    }
    zkw::work();
    int t = zkw::MinCost;
    if(zkw::MaxFlow < 1)
        puts("No Solution!");
    else{
        std::cout << t << std::endl;
        for(int i = 0; i < zkw::idx; i += 2){
            zkw::Edge e = zkw::edge[i];
            if(n + e.u == e.v){
                continue;
            }
            else{
                if(e.f != zkw::INF){
                    G[e.u-n].push_back(e.v);
                    G[e.v].push_back(e.u-n);
                }
            }
        }
        dfs(1);
        std::cout << node[1] << std::endl;
    }
    return 0;
}