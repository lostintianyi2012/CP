/*
 * Copyright© 2023 lsty. All rights reserved.
 * author: lsty
 * Problem: P6600
 * Tag: PrefixSum
 * Date: 2023-02-20 
 */
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <algorithm>

using namespace std;
const int N = 3e3 + 10;
int g[N][N];
int l[N][N], r[N][N], d[N][N];
long long minh[N];
long long sumh[N];
long long minw[N];
int a, b, s, x;
int n, m;

int main() {
    scanf("%d%d", &n, &m);
    scanf("%d%d%d%d", &a, &b, &s, &x);
    a = max(a, 3), b = max(b, 2);
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= m; j++){
            scanf("%1d", &g[i][j]);
        }
    }

    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= m; j++){
            if(g[i][j])
                l[i][j] = l[i][j-1] + 1;
        }
        for(int j = m; j >= 1; j--){
            if(g[i][j])
                r[i][j] = r[i][j+1] + 1;
        }
    }

    for(int i = n; i >= 1; i--){
        for(int j = 1; j <= m; j++){
            if(g[i][j])
                d[i][j] = d[i+1][j] + 1;
        }
    }

    for(int w = a + !(a & 1); w <= m; w += 2){
        //对于每个 w 的不合法的数量
        minh[w] = max((int)ceil(s * 1.0 / w), max(x - w, b)) - 1;
        sumh[w] = sumh[w-2] + minh[w];
    }

    int w = a + !(a & 1);
    for(int i = n; i >= b; i--){
        while(w <= m && minh[w] > i)   w += 2;
        minw[i] = w;
    }

    long long ans = 0;
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= m; j++){
            if(!g[i][j])
                continue;
            long long maxh = d[i][j];
            long long maxn = 1ll * 2 * min(r[i][j], l[i][j]) - 1;
            long long minn = minw[maxh];
            if(maxn < minn || maxh < b)
                continue;
            ans += 1ll * (maxn - (minn - 2)) / 2 * maxh - (sumh[maxn] - sumh[minn-2]);
        }
    }
    printf("%lld\n", ans);
    return 0;
}