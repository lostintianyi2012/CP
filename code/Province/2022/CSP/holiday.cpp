#include <bits/stdc++.h>

using namespace std;
const int N = 2510, M = 2e4 + 10;
const int inf = 0x3f3f3f3f;
typedef pair<long long, int> PII;
int e[M], ne[M], h[N], G[N][N], idx;
long long w[N];
PII f[N][3];
bool st[N];
int n, m, k;

inline void add(int a, int b){
    e[idx] = b, ne[idx] = h[a], h[a] = idx++;
    e[idx] = a, ne[idx] = h[b], h[b] = idx++;
}

bool cmp(PII a, PII b){
    return a.first > b.first;
}

void bfs(int z){
    queue<int> q;
    q.push(z);
    G[z][z] = -1;
    while(!q.empty()){
        int u = q.front();
        q.pop();
        for(int i = h[u]; ~i; i = ne[i]){
            int v = e[i];
            if(G[z][v] != inf)
                continue;
            
            G[z][v] = G[z][u] + 1;
            q.push(v);

            //如果这个点在家附近并且从这个点出发可以到达
            if(st[v] && G[z][v] <= k){
                PII tmp[4];
                for(int i = 0; i < 3; i++)
                    tmp[i] = f[z][i];
                tmp[3].first = w[v];
                tmp[3].second = v;
                sort(tmp, tmp + 4, cmp);
                for(int i = 0; i < 3; i++)
                    f[z][i] = tmp[i];
            }
        }
    }
    
}

int main(){
    memset(h, -1, sizeof h);
    memset(G, 0x3f, sizeof G);
    scanf("%d%d%d", &n, &m, &k);
    for(int i = 2; i <= n; i++){
        scanf("%lld", &w[i]);
    }
    for(int i = 1; i <= m; i++){
        int a, b;
        scanf("%d%d", &a, &b);
        add(a, b);
    }
    for(int i = 1; i <= n; i++){
        for(int j = 0; j < 3; j++)
            f[i][j] = {-1, 0};
    }
    
    st[1] = false;
    queue<int> q;
    q.push(1);
    G[1][1] = -1;
    while(!q.empty()){
        int u = q.front();
        q.pop();
        for(int i = h[u]; ~i; i = ne[i]){
            int v = e[i];
            if(G[1][v] != inf)
                continue;

            G[1][v] = G[1][u] + 1;
            q.push(v);

            if(G[1][v] <= k)
                st[v] = true;
        }
    }

    for(int i = 2; i <= n; i++){
        bfs(i);
    }
    
    long long ans = -1;
    for(int b = 2; b <= n; b++){
        for(int c = 2; c <= n; c++){
            if(G[b][c] > k || b == c)
                continue;
            for(int i = 0; i < 3; i++){
                int a = f[b][i].second;
                if(a == 0) 
                    break;
                for(int j = 0; j < 3; j++){
                    int d = f[c][j].second;
                    if(d == 0)
                        break;
                    if(d == a || b == c || a == c || d == b)
                        continue;
                    ans = max(ans, w[a] + w[b] + w[c] + w[d]);
                }
            }
        }
    }
    printf("%lld\n", ans);
    return 0;
}