/*
 * Copyright© 2023 lsty. All rights reserved.
 * author: lsty
 * Problem: Multiplication Puzzle
 * Tag: Segment DP
 * Date: 2023-02-20 
 */
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>

using namespace std;
const int INF = 0x3f3f3f3f;
const int N = 110;
long long dp[N][N];
int n;
int a[N];

int main() {
    scanf("%d", &n);
    for(int i = 1; i <= n; i++){
        scanf("%d", &a[i]);
    }

    for(int len = 1; len < n; len++){
        for(int i = 2; i + len - 1 <= n - 1; i++){
            int j = i + len - 1;
            dp[i][j] = INF;
            for(int k = i; k <= j; k++){
                dp[i][j] = min(dp[i][j], dp[i][k-1] + dp[k + 1][j] + (long long)a[k] * a[i-1] * a[j+1]);
            }
        }
    }
    printf("%lld\n", dp[2][n-1]);
    return 0;
}