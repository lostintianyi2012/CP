/*
 * Copyright© 2023 lsty. All rights reserved.
 * author: lsty
 * Problem: P4124 手机号码
 * Tag: 数位DP
 * Date: 2023-02-20 
 */
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>

using namespace std;
const int N = 15;
long long dp[N][N][N][2][2][2][2];
long long l, r;
int a[N];

long long dfs(int u, int k, int last, bool ok, bool lim, bool has_4, bool has_8){
    if(has_4 && has_8)
        return 0;
    if(u == 0)
        return ok;
    if(dp[u][k][last][ok][lim][has_4][has_8] != -1)
        return dp[u][k][last][ok][lim][has_4][has_8];

    int maxn = lim ? a[u] : 9;
    long long ans = 0;
    for(int i = 0; i <= maxn; i++){
        ans += dfs(u - 1, i, k, ok || (i == k && i == last),lim && (i == maxn), has_4 || (i == 4), has_8 || (i == 8));
    }
    dp[u][k][last][ok][lim][has_4][has_8] = ans;
    return ans;
}

long long work(long long x){
    if(x < 1e10)
        return 0;
    memset(dp, -1, sizeof dp);
    int idx = 0;
    while(x){
        a[++idx] = x % 10;
        x /= 10;
    }
    long long ans = 0;
    for(int i = 1; i <= a[idx]; i++)
        ans += dfs(idx - 1, i, 0, 0, i == a[idx], i == 4, i == 8);
    return ans;
}

int main() {
    scanf("%lld%lld", &l, &r);
    printf("%lld\n", work(r) - work(l-1));
    return 0;
}