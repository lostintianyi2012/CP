#include <iostream>
#include <string.h>
#include <stdio.h>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;
const int N = 5e4 + 10, M = 1e5 + 10;
int h[N], e[M], ne[M], w[M], idx;
multiset<int> f[N];
int n, m;
int lim;
int chain_num;

void add(int u, int v, int c){
    e[idx] = v, ne[idx] = h[u], w[idx] = c, h[u] = idx++;
}

//dfs表示求出当前的限制之下最多能开出几条链

int dfs(int u, int fa){
    int maxn = 0;
    f[u].clear();
    int k;
    for(int i = h[u]; ~i; i = ne[i]){
        int v = e[i];
        if(v == fa)
            continue;
        k = dfs(v, u) + w[i];
        if(k >= lim)
            chain_num++;
        else{
            f[u].insert(k);
        }
    }
    multiset<int>::iterator it;
    while(!f[u].empty()){
        if(f[u].size() == 1)
            return max(maxn, *f[u].begin());
        it = f[u].lower_bound(lim - *f[u].begin());

        if(it == f[u].begin() && f[u].count(*it) == 1)
            it++;
        if(it == f[u].end()){
            maxn = max(maxn, *f[u].begin());
            f[u].erase(f[u].find(*f[u].begin()));
        }
        else{
            chain_num++;
            f[u].erase(f[u].find(*f[u].begin()));
            f[u].erase(f[u].find(*it));
        }
    }
    return maxn;
}

bool check(int x){
    lim = x;
    chain_num = 0;
    dfs(1, -1);
    return chain_num >= m;
}

int main(){
    memset(h, -1, sizeof h);
    scanf("%d%d", &n, &m);
    int sumc = 0;
    for(int i = 1; i < n; i++){
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        add(a, b, c), add(b, a, c);
        sumc += c;
    }

    int l = 1, r = sumc + 100000;
    int ans = 0;
    while(l < r){
        int mid = (l + r) >> 1;
        if(check(mid))  {ans = mid, l = mid + 1;}
        else    r = mid;
    }
    printf("%d\n", ans);
    return 0;
}