/* 
 * Author:lsty
 * Date:2023.1.26
 * Problem:P2024 食物链
 * Tag:DSU
 */
#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;
const int N = 5e4 + 10;
int d[N], fa[N];
int x, y;
int n, k;
int ans = 0;

int find(int x){
    if(x != fa[x]){
        int t = fa[x];
        fa[x] = find(t);
        d[x] = (d[x] + d[t]) % 3;
    }
    return fa[x];
}

void merge(int x, int y, int op){
    int fx = find(x), fy = find(y);
    if(fx == fy){
        if((op - 1) ^ ((d[x] - d[y] + 3) % 3))
            ans ++;
    }
    else{
        fa[fx] = fy;
        d[fx] = (d[y] - d[x] + op - 1) % 3;
    }
}

int main(){
    scanf("%d%d", &n, &k);
    for(int i = 0; i <= n; i++){
        fa[i] = i;
    }

    for(int i = 1; i <= k; i++){
        int op;
        scanf("%d%d%d", &op, &x, &y);

        if(x > n || y > n || (op == 2 && x == y))   ans ++;
        else{
            merge(x, y, op);
        }
    }

    printf("%d\n", ans);
    return 0;
}