/*
 * Copyright© 2023 lsty. All rights reserved.
 * author: lsty
 * Problem: POJ1741 Tree
 * Tag: 点分治
 * Date: 2023-02-27
 */
#include <algorithm>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace std;
const int N = 10100;
int h[N], e[N << 1], ne[N << 1], w[N << 1];
int n, k, idx;
//距离重心的距离, 重心, 子树大小
int dis[N], root, siz[N];
bool vis[N];
//最大子树最小的大小
int MinMax;
int ans;
//路径个数
int ways;

void add(int x, int y, int z)
{
    e[idx] = y, ne[idx] = h[x], w[idx] = z, h[x] = idx++;
}

void getsize(int u, int fa){
    siz[u] = 1;
    for(int i = h[u]; ~i; i = ne[i]){
        int v = e[i];
        if(v == fa || vis[v])
            continue;
        getsize(v, u);
        siz[u] += siz[v];
    }
    return ;
}

//找根节点
void getroot(int u, int tot, int fa){
    int Maxn = tot - siz[u];
    for(int i = h[u]; ~i; i = ne[i]){
        int v = e[i];
        if(v == fa || vis[v])
            continue;
        getroot(v, tot, u);
        Maxn = max(Maxn, siz[v]);
    }
    if(Maxn < MinMax){
        root = u;
        MinMax = Maxn;
    }
}

//所有节点和重心的距离
void getdis(int u, int d, int fa){
    dis[++ways] = d;
    for(int i = h[u]; ~i; i = ne[i]){
        int v = e[i];
        if(v == fa || vis[v])
            continue;
        getdis(v, d + w[i], u);
    }
}

int work(int u, int d){
    ways = 0;
    getdis(u, d, 0);
    sort(dis + 1, dis + 1 + ways);
    int uans = 0, i = 1, j = ways;
    while(i < j){
        while(i < j && dis[i] + dis[j] > k) j--;
        uans += j - i;
        i++;
    }
    return uans;
}

void dfs(int x){
    ways = 0;
    MinMax = N << 1;
    getsize(x, 0);
    getroot(x, siz[x], 0);
    ans += work(root, 0);
    vis[root] = 1;
    for(int i = h[root]; ~i; i = ne[i]){
        int v = e[i];
        //容斥, 减去会重复算的
        if(vis[v])
            continue;
        ans -= work(v, w[i]);
        dfs(v);
    }
}

int main()
{
    while (scanf("%d%d", &n, &k) != EOF && n && k) {
        memset(vis, 0, sizeof(vis));
        memset(h, -1, sizeof(h));
        idx = 0;
        root = 1;
        ans = 0;
        for (int i = 1; i <= n-1; i++) {
            int x, y, z;
            scanf("%d%d%d", &x, &y, &z);
            add(x, y, z), add(y, x, z);
        }
        dfs(1);
        printf("%d\n", ans);
    }
    return 0;
}