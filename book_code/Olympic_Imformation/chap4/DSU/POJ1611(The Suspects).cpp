/* 
 * Author:lsty
 * Date:2023.1.26
 * Problem:POJ 1611 The Suspects
 * Tag:DSU
 */
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;
const int N = 3e4 + 10;
int fa[N];
int d[N];
int n, m;

int find(int x){
    if(x != fa[x]){
        int t = fa[x];
        fa[x] = find(t);
    }
    return fa[x];
}

void merge(int x, int y){
    int fx = find(x), fy = find(y);
    if(fx == fy){
        return ;
    }
    if(fx < fy)
        swap(fx, fy);
    //编号大的所属的集合接到编号小的所属的上
    fa[fx] = fy;
    d[fy] += d[fx];
}

int main(){
    while(scanf("%d%d", &n, &m) && (n || m)){
        for(int i = 0; i < n; i++){
            fa[i] = i;
            d[i] = 1;
        }

        for(int i = 0; i < m; i++){
            int k;
            scanf("%d", &k);
            int rt;
            scanf("%d", &rt);
            for(int i = 1; i < k; i++){
                int t;
                scanf("%d", &t);
                merge(rt, t);
            }
        }

        printf("%d\n", d[0]);
    }
    return 0;
}
