/*
 * Author:lsty
 * Date:2023.2.7
 * Problem:2019 CSP-S D1 括号树
 * Tag:stack
 */
#include <iostream>
#include <string.h>
#include <algorithm>
#include <vector>
#include <stack>

const int N = 1e6 + 10, M = 5e5 + 10;
int e[N], ne[N];
int fa[M], h[M], idx;
int con[M];
long long f[M];
int n;
long long ans;
char w[M];

void add(int x, int y){
    e[++idx] = y, ne[idx] = h[x], h[x] = idx;
}

std::stack<int> stk;
void dfs(int u, int fath){
    int k = 0;
    if(w[u] == '('){
        stk.push(u);
    }
    else if(!stk.empty()){
        k = stk.top();
        stk.pop();
        con[u] = con[fa[k]] + 1;
    }
    f[u] = f[fa[u]] + con[u];
    ans ^= (long long)f[u] * (long long)u;
    for(int i = h[u]; i; i = ne[i]){
        int v = e[i];
        if(v != fath)
            dfs(v, u);
    }
    if(k)
        stk.push(k);
    else if(!stk.empty())
        stk.pop();
}

int main(){
    scanf("%d", &n);
    scanf("%s", w + 1);
    for(int i = 2; i <= n; i ++){
        int k;
        scanf("%d", &k);
        add(i, k), add(k, i);
        fa[i] = k;
    }
    dfs(1, 0);
    printf("%lld\n", ans);
    return 0;
}