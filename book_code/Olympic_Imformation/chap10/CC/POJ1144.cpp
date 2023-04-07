/*
 * Copyright© 2023 lsty. All rights reserved.
 * author: lsty
 * Problem: POJ 1144 Network
 * Tag: Template, DCC
 * Date: 2023-02-23 
 */
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>

using namespace std;
const int N = 110, M = 2 * N * N;
int h[N], e[M], ne[M], idx;
int low[N], dfn[N], cnt;
bool cut[N];
int n;

void add(int x, int y){
    e[idx] = y, ne[idx] = h[x], h[x] = idx++;
}

void tarjan(int u, int fa){
    low[u] = dfn[u] = ++cnt;
    int child = 0;

    for(int i = h[u]; ~i; i = ne[i]){
        int v = e[i];
        if(v == fa)
            continue;
        
        //新点
        if(!dfn[v]){
            //回退边不计入子树
            child++;
            tarjan(v, u);
            low[u] = min(low[u], low[v]);

            if(low[v] >= dfn[u] && u != 1)
                cut[u] = true;
        }
        //回退边
        else if(dfn[v] && dfn[v] < dfn[u]){
            low[u] = min(low[u], dfn[v]);
        }
    }
    if(u == 1 && child > 1)
        cut[u] = true;
}

void clear(){
    memset(h, -1, sizeof h);
    memset(low, 0, sizeof low);
    memset(dfn, 0, sizeof dfn);
    memset(cut, 0, sizeof cut);
    cnt = 0, idx = 0;
}

int main() {
    while(1){
        clear();
        scanf("%d", &n);
        if(n == 0)
            break;
        while(1){
            int x;
            scanf("%d", &x);
            if(x == 0)
                break;
            int y;
            while(getchar() != '\n'){
                scanf("%d", &y);
                add(x, y), add(y, x);
            }
        }

        tarjan(1, -1);
        int ans = 0;
        for(int i = 1; i <= n; i++)
            ans += cut[i];
        printf("%d\n", ans);
    }
    return 0;
}