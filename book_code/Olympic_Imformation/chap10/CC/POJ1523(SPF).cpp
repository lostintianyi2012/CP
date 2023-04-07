/*
 * Copyright© 2023 lsty. All rights reserved.
 * author: lsty
 * Problem: POJ1523 SPF
 * Tag: DCC
 * Date: 2023-02-22 
 */
#include <stack>
#include <queue>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>

using namespace std;
const int N = 1010, M = 2e6 + 10;
int h[N], e[M], ne[M], idx;
int low[N], dfn[N], tot;
bool cut[N];
int cnt[N];
int n;

void add(int x, int y){
    e[idx] = y, ne[idx] = h[x], h[x] = idx++;
}

void dfs(int u, int fa){
    low[u] = dfn[u] = ++tot;
    int child = 0;
    for(int i = h[u]; ~i; i = ne[i]){
        int v = e[i];
        if(v == fa)
            continue;
        
        //没有访问过的节点
        if(!dfn[v]){
            child++;
            dfs(v, u);
            low[u] = min(low[u], low[v]);
            if(low[v] >= dfn[u] && u != 1){
                cut[u] = true;
                cnt[u]++;
            }
        }
        //回退边
        else if(dfn[v] < dfn[u])
            low[u] = min(low[u], dfn[v]);
    }
    if(u == 1 && child >= 2){
        cut[1] = true;
        cnt[1] = child;
    }
    //printf("Node#%d low[u]:%d\n", u, low[u]);
}

void tarjan(){
    memset(cnt, 0, sizeof(cnt));
    memset(cut, 0, sizeof(cut));
    memset(low, 0, sizeof(low));
    memset(dfn, 0, sizeof(dfn));
    dfs(1, -1);
}

int main() {
    for(int CASENUM = 1; ; CASENUM++){
        bool flag = true;
        memset(h, -1, sizeof(h));
        n = 0, idx = 0, tot = 0;
        while(1){
            int x, y;
            scanf("%d", &x);
            if(!x)
                break;
            else{
                flag = false;
                scanf("%d", &y);
                add(x, y), add(y, x);
            }
            n = max(n, x);
            n = max(n, y);
        }

        if(flag)
            break;
        
        tarjan();
        queue<int> t;
        for(int i = 1; i <= n; i++){
            if(cut[i]){
                t.push(i);
            }
        }
        printf("Network #%d\n", CASENUM);
        if(t.empty()){
            printf("  No SPF nodes\n");
        }
        else{
            while(!t.empty()){
                int u = t.front();
                t.pop();
                int k = 0;
                if(u == 1)
                    k = cnt[u];
                else
                    //父亲还有
                    k = cnt[u] + 1;
                printf("  SPF node %d leaves %d subnets\n", u, k);
            }
        }
        printf("\n");
    }
    return 0;
}