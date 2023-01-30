/*
 * Author:lsty
 * Date:2023.1.27
 * Problem:P1525 关押罪犯
 * Tag:DSU 边上维护循环群
 */
#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;
const int N = 20010, M = 100010;
int d[N];
int fa[N];
int n, m;
struct event{
    int x, y, val;
}edge[M];

inline int read(){
    int w = 1, s = 0;
    char c = getchar();
    while(!isdigit(c)){
        if(c == '-')
            w = -1;
        c = getchar();
    }
    while(isdigit(c)){
        s = (s << 3) + (s << 1) + (c ^ 48);
        c = getchar();
    }
    return w * s;
}

int find(int x){
    if(fa[x] != x){
        int t = fa[x];
        fa[x] = find(t);
        d[x] = (d[x] + d[t]) & 1;
    }
    return fa[x];
}

bool merge(int x, int y){
    int fx = find(x), fy = find(y);
    if(fx == fy){
        int k = (d[x] + d[fx] - d[y]) & 1;
        if(k == 0)
            return true;
        else
            return false;
    }
    else{
        fa[fx] = fy;
        d[fx] = (d[y] + 1 - d[x]) & 1;
        return false;
    }
}

inline bool cmp(const event& a, const event& b){
    return a.val > b.val;
}

int main(){
    n = read(), m = read();
    for(int i = 1; i<= n; i++){
        fa[i] = i;
    }
    for(int i = 0; i < m; i++){
        edge[i].x = read();
        edge[i].y = read();
        edge[i].val = read();
    }
    sort(edge, edge + m, cmp);

    bool flag = false;
    for(int i = 0; i < m; i++){
        if(merge(edge[i].x, edge[i].y)){
            printf("%d\n", edge[i].val);
            flag = true;
            break;
        }
        else{
            continue;
        }
    }
    if(!flag){
        printf("0\n");
    }

    return 0;
}