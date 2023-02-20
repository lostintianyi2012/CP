/*
 * Copyright© 2023 lsty. All rights reserved.
 * author: lsty
 * Problem:
 * Tag:
 * Date: 2023-02-18 
 */
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
#include <string.h>

using namespace std;
const int N = 2e3 + 10;
int dp[N][N];
char w1[N], w2[N];
int main() {
    scanf("%s", w1 + 1);
    scanf("%s", w2 + 1);
    int n = strlen(w1 + 1);
    int m = strlen(w2 + 1);
    for(int i = 1; i <= n; i++)
        dp[i][0] = i;
    for(int i = 1; i <= m; i++)
        dp[0][i] = i;
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= m; j++){
            if(w1[i] == w2[j])
                dp[i][j] = dp[i-1][j-1];
            else
                dp[i][j] = min(dp[i-1][j-1], min(dp[i-1][j], dp[i][j-1])) + 1;
        }
    }
    printf("%d\n", dp[n][m]);
    return 0;
}