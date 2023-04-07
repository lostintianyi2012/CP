---
aliases: P2657 Windy数
date: 2023-02-20
type: Solution
tags: 数位DP
---
# P2657 题解
## 题意
求 $[a,b]$ 中有多少个数不含前导 $0$ 且相邻两数之差至少为 $2$

## 做法
很显然是用数位DP做, 由于相邻两位的限制, 设计状态的时候要涉及到最高位, 所以设 $dp[i][j]$ 表示最高位是 $i$, 总共 $j$ 位的方案数
记忆化搜索即可
```cpp
/*
 * Copyright© 2023 lsty. All rights reserved.
 * author: lsty
 * Problem: P2657 Windy数
 * Tag: 数位DP, 记忆化搜索
 * Date: 2023-02-20 
 */
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
#include <string.h>

using namespace std;
typedef long long ll;
const int N = 12;
//dp[i][j]上一位取值为i, 共 j 位
ll dp[N][N];
int a[N], idx;

//上一位取值为last
int dfs(int u, int last, bool lead, bool lim){
    if(u == 0)
        return 1;
    if(!lead && !lim && dp[last][u] != -1)
        return dp[last][u];

    //这一位的取值
    int maxn = lim ? a[u] : 9;
    int ans = 0;
    for(int i = 0; i <= maxn; i++){
        //如果有前导0, 可以忽略相邻两数差的限制
        if(lead){
            ans += dfs(u-1, i, i == 0, lim && i == maxn);
        }
        else{
            if(abs(last - i) >= 2)
                ans += dfs(u-1, i, false, lim && i == maxn);
        }
    }
    if(!lead && !lim)
        dp[last][u] = ans;
    return ans;
}

//找[1, x]之间有多少个windy数
int solve(int x){
    idx = 0;
    while(x){
        a[++idx] = x % 10;
        x /= 10;
    }
    return dfs(idx, 0, true, true);
}

int main() {
    memset(dp, -1, sizeof(dp));
    int a, b;
    scanf("%d%d", &a, &b);
    printf("%d\n", solve(b) - solve(a-1));
    return 0;
}
```