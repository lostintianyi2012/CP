/*
 * Author:lostintianyi
 * Date:2023.1.25
 * Problem:P3295
 * Tag:multiply, Disjoint-set
 */
#include <bits/stdc++.h>

using namespace std;
const int N = 1e5 + 10, mod = 1e9 + 7;
int fa[20][N];
int n, m;
int l1, r1, l2, r2;

inline int find(int x, int k){
    return fa[k][x] == x ? x : fa[k][x] = find(fa[k][x], k);
}

inline void merge(int x, int y, int k){
    int fx = find(x, k), fy = find(y, k);
    if(fx ^ fy)
        fa[k][fx] = fy;
}

int main(){
    scanf("%d%d", &n, &m);
    int maxk = log2(n);
    for(int k = 0; k <= maxk; k++){
        for(int i = 1; i <= n; i++){
            fa[k][i] = i;
        }
    }

    for(int i = 1; i <= m; i ++){
        scanf("%d%d%d%d", &l1, &r1, &l2, &r2);

        for(int k = maxk; k >= 0; k--){
            if(l1 + (1 << k) - 1 <= r1){
                merge(l1, l2, k);
                l1 += 1 << k;
                l2 += 1 << k;
            }
        }

    }

    for(int k = maxk; k; k--){
        for(int i = 1; i + (1 << k) - 1 <= n; i++){
            int fi = find(i, k);
            int i2 = i + (1 << (k-1));
            int fi2 = fi + (1 << (k-1));
            merge(i, fi, k-1), merge(i2, fi2, k-1);
        }
    }

    long long ans = 0;
    for(int i = 1; i <= n; i++){
        if(fa[0][i] == i)
            ans = !ans ? 9 : ans * 10 % mod;
    }
    printf("%lld\n", ans);
    return 0;
}