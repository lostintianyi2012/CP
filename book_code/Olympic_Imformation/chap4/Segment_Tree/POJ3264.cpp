/*
 * Author:lsty
 * Date:2023.2.13
 * Problem:POJ#3264 Balanced Lineup
 * Tag:线段树
 */
#include <iostream>
#include <string.h>
#include <algorithm>
#include <stdio.h>

const int N = 5e4 + 10;
int a[N];
int n, m;

inline char getc(){
    static char buf[N], *p1 = buf, *p2 = buf;
    return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, N, stdin), p1 == p2) ? EOF : *p1++;
}

inline long long read(){
    long long s = 0, w = 1;
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
    return s * w;
}

struct node{
    int l, r;
    int max, min;
}tr[N << 2];

void pushup(int u){
    node ls = tr[u << 1], rs = tr[u << 1 | 1];
    tr[u].max = std::max(ls.max, rs.max);
    tr[u].min = std::min(ls.min, rs.min);
}

void build(int u, int l, int r){
    tr[u].l = l, tr[u].r = r;
    if(l == r)
        tr[u].max = tr[u].min = a[l];
    else{
        int mid = (l + r) >> 1;
        build(u << 1, l, mid);
        build(u << 1 | 1, mid + 1, r);
        pushup(u);
    }
}

int query_max(int u, int l, int r){
    if(l <= tr[u].l && tr[u].r <= r){
        return tr[u].max;
    }
    else{
        int mid = tr[u].l + tr[u].r >> 1;
        int max = 0;
        if(l <= mid)    max = std::max(max, query_max(u << 1, l, r));
        if(r > mid)     max = std::max(max, query_max(u << 1 | 1, l, r));
        return max;
    }
}

int query_min(int u, int l, int r){
    if(l <= tr[u].l && tr[u].r <= r){
        return tr[u].min;
    }
    else{
        int mid = tr[u].l + tr[u].r >> 1;
        int min = 0x3f3f3f3f;
        if(l <= mid)    min = std::min(min, query_min(u << 1, l, r));
        if(r > mid)     min = std::min(min, query_min(u << 1 | 1, l, r));
        return min;
    }
}

int main(){
    n = read(), m = read();
    for(int i = 1; i <= n; i++)
        a[i] = read();
    build(1, 1, n);
    for(int i = 1; i <= m; i++){
        int l = read(), r = read();
        printf("%d\n", query_max(1, l, r) - query_min(1, l, r));
    }
    return 0;
}