/*
 * Author:lsty
 * Date:2023.2.13
 * Problem:P1099 树网的核
 * Tag:树的直径
 */
#include <iostream>
#include <string.h>
#include <algorithm>
#include <deque>
#include <stdio.h>
#include <cstdlib>

const int N = 5e5 + 10;
int e[N << 1], ne[N << 1], h[N], w[N << 1];
int dis[N], fa[N];
int n, s, idx;
int k, ans = 0x3f3f3f3f;
bool mark[N];
/**********************************************/
inline char getc(){
    static char buf[100000], *p1, *p2;
    return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 100000, stdin), p1 == p2) ? EOF : *p1++;
}

inline long long read(){
    long long s = 0;
    int w = 1;
    char c = getc();
    while(!isdigit(c)){
        if(c == '-')
            w = -1;
        c = getc();
    }
    while(isdigit(c)){
        s = (s << 3) + (s << 1) + (c ^ 48);
        c = getc();
    }
    return w * s;
}
/**********************************************/

void add(int u, int v, int c){
    e[idx] = v, ne[idx] = h[u], w[idx] = c, h[u] = idx++;
}

void dfs(int u, int fath){
    fa[u] = fath;
    if(dis[u] > dis[k])
        k = u;
    for(int i = h[u]; ~i; i = ne[i]){
        int v = e[i];
        if(v == fath || mark[v])
            continue;
        dis[v] = dis[u] + w[i];
        dfs(v, u);
    }
}

int main(){
    memset(h, -1, sizeof h);
    n = read(), s = read();
    for(int i = 1; i < n; i++){
        int a, b, c;
        a = read(), b = read(), c = read();
        add(a, b, c), add(b, a, c);
    }
    dis[1] = 0, dfs(1, 0);
    int st = k;
    dis[k] = 0, dfs(k, 0);
    int ed = k;
    int i = ed, j = ed;
    while(i){
        while(dis[j] - dis[i] > s) j = fa[j];
        //一条链上
        int tmp = std::max(dis[i], dis[ed] - dis[j]);
        ans = std::min(ans, tmp);
        i = fa[i];
    }
    for(int i = ed; i; i = fa[i])   mark[i] = true;
    //在尺取的过程中, 我们总是维护一条链, 因为我们知道一个结论:树上一个点到直径端点的距离最大
    //但是可能存在这样的情况: 链内的某一个点到其他分支的距离虽然小于到端点距离, 但是却比链端点到直径端点距离大
    //在刚刚整个链同时维护的时候没有考虑到这种情况, 接下来的 DFS 不在直径上走, 而是向各个支链找对应的答案
    for(int i = ed; i; i = fa[i]){
        dis[i] = 0, k = i;
        //从每个点只找支链, O(n)
        dfs(i, fa[i]);
    }
    for(int i = 1; i <= n; i++){
        ans = std::max(ans, dis[i]);
    }
    printf("%d\n", ans);
    return 0;
}