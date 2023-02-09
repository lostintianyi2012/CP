#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <vector>

const int N = 110;
int f[N][N][N];
int g[N][N];
int sum[N][N];

int main(){
    int n, m;
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= m; j++){
            scanf("%d", &g[i][j]);
        }
    }

    //f[i][j][k] 表示前 i 行, 这一列选了 j 个, 其他列选了 k 个的不合法方案数量
    //f[i][j][k] = f[i-1][j][k] + a[i][col] * f[i-1][j-1][k] + (s[i] - a[i][col]
    for(int col = 1; col <= m; col++){

    return 0;
}