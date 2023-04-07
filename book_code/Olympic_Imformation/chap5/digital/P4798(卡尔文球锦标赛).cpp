/*
 * Copyright© 2023 lsty. All rights reserved.
 * author: lsty
 * Problem: CEOI2015 卡尔文球锦标赛
 * Tag: 数位DP
 * Date: 2023-02-23 
 */
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>

using namespace std;
typedef long long ll;
const int N = 1e4 + 10;
const int mod = 1e6 + 7;
ll dp[2][2][N];
int a[N];
int n;

int main() {
    scanf("%d", &n);
    for(int i = 1; i <= n; i++)
        scanf("%d", &a[i]);
    dp[1][1][1] = 1;

    for(int i = 1; i < n; i++){
        int nxt = (i & 1) ^ 1;
        int ths = (i & 1);
        for(int j = 1; j <= i; j++){
            dp[ths][0][j] %= mod, dp[ths][1][j] %= mod;
            dp[nxt][0][j] += dp[ths][0][j] * j;
            dp[nxt][0][j+1] += dp[ths][0][j];
            

            dp[nxt][0][j] += dp[ths][1][j] * (a[i+1]-1);
            if(a[i+1] == j + 1){
                dp[nxt][1][j+1] += dp[ths][1][j];
            }
            else{
                dp[nxt][1][j] += dp[ths][1][j];
            }
            dp[ths][0][j] = dp[ths][1][j] = 0;
        }
    }
    //完美符合字典序还有一种
    ll ans = 1;
    int p = n & 1;
    for(int i = 1; i <= n; i++){
        dp[p][0][i] %= mod;
        ans += dp[p][0][i];
        if(ans > mod)
            ans -= mod;
    }
    printf("%lld\n", ans);
    return 0;
}