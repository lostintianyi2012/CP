/* 
 * Author:lsty
 * Date:2023.1.26
 * Problem:POJ 2425 Ubiquitous Religions
 * Tag:DSU
 */
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;
const int N = 50010;
int fa[N];
int n, m;

int find(int x){
    if(fa[x] != x){
        fa[x] = find(fa[x]);
    }
    return fa[x];
}

void merge(int x, int y){
    int fx = find(x), fy = find(y);
    if(fx != fy){
        fa[fx] = fy;
    }
}

int main(){
    int casenum = 1;
    while(scanf("%d%d", &n, &m) && (n || m)){
        for(int i = 1; i <= n; i++){
            fa[i] = i;
        }
        
        for(int i = 1; i <= m; i++){
            int x, y;
            scanf("%d%d", &x, &y);
            merge(x, y);
        }

        int ans = 0;
        for(int i = 1; i <= n; i++){
            if(fa[i] == i)
                ans++;
        }
        printf("Case %d: %d\n", casenum++, ans);
    }
    return 0;
}