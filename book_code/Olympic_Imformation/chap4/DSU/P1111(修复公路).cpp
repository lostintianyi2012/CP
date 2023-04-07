/* 
 * Author:lsty
 * Date:2023.1.27
 * Problem:P1111 修复公路
 * Tag:DSU
 */
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int N = 1010, M = 100010;
int fa[N];
int d[N];
int n, m;
bool st[N];

struct node{
    int x, y, t;
    bool operator < (const node& b) const {
        return t < b.t;
    }
}road[M];

int find(int x){
    if(x != fa[x]){
        fa[x] = find(fa[x]);
    }
    return fa[x];
}

void merge(int x, int y){
    int fx = find(x), fy = find(y);
    if(fx == fy){
        return ;
    }
    else{
        if(fy > fx){
            swap(fx, fy);
        }
        fa[fx] = fy;
        d[fy] += d[fx];
    }
}

int main(){
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; i++){
        fa[i] = i;
        d[i] = 1;
    }

    for(int i = 1; i <= m; i++){
        scanf("%d%d%d", &road[i].x, &road[i].y, &road[i].t);
    }
    sort(road + 1, road + 1 + m);

    for(int i = 1; i <= m; i++){
        int x0 = road[i].x, y0 = road[i].y;
        merge(x0, y0);
        if(d[1] == n){
            printf("%d\n", road[i].t);
            break;
        }
    }
    if(d[1] != n){
        printf("-1\n");
    }
    return 0;
}