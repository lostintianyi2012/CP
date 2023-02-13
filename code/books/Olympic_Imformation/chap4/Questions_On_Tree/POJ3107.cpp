/*
 * Author:lsty
 * Date:2023.2.13
 * Problem:POJ 3017 GodFather
 * Tag:树的重心
 */
#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <string.h>

inline char getc(){
    static char buf[10000], *p1 = buf, *p2 = buf;
    return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 10000, stdin), p1 == p2) ? EOF : *p1++;
}

inline long long read(){
    int w = 1;
    long long x = 0;
    char c = getc();
    while(!isdigit(c)){
        if(c == '-')
            w = -1;
        c = getc();
    }
    while(isdigit(c)){
        x = (x << 3) + (x << 1) + (c ^ 48);
        c = getc();
    }
    return x * w;
}

const int N = 5e4 + 10;
int e[N << 1], ne[N << 1], h[N], idx;
int c[N];
int n;
int maxnum = 0x3f3f3f3f, ans[N], cnt;

void add(int a, int b){
    e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}

void dfs(int u, int fa){
    c[u] = 1;
    int tmp = 0;
    for(int i = h[u]; ~i; i = ne[i]){
        int v = e[i];
        if(v == fa)
            continue;
        dfs(v, u);
        c[u] += c[v];
        tmp = std::max(tmp, c[v]);
    }
    tmp = std::max(tmp, n - c[u]);
    if(tmp < maxnum){
        maxnum = tmp;
        cnt = 0;
        ans[++cnt] = u;
    }
    else if(tmp == maxnum)
        ans[++cnt] = u;
}

int main(){
    memset(h, -1, sizeof h);
    n = read();
    for(int i = 1; i < n; i++){
        int u = read(), v = read();
        add(u, v), add(v, u);
    }
    dfs(1, -1);

    std::sort(ans + 1, ans + 1 + cnt);
    for(int i = 1; i <= cnt; i++){
        printf("%d ", ans[i]);
    }
    return 0;
}