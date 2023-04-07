#include <iostream>
#include <algorithm>
#include <string.h>
#include <queue>

const int N = 351, M = 41;
long long dp[M][M][M][M];
int a[N];
int cnt[5];

int main(){
    int n, m;
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; i++){
        scanf("%d", &a[i]);
    }
    for(int i = 1; i <= m; i++){
        int t;
        scanf("%d", &t);
        cnt[t]++;
    }
    dp[0][0][0][0] = a[1];
    for(int i = 0; i <= cnt[1]; i++){
        for(int j = 0; j <= cnt[2]; j++){
            for(int k = 0; k <= cnt[3]; k++){
                for(int l = 0; l <= cnt[4]; l++){
                    int t = i * 1 + j * 2 + k * 3 + l * 4 + 1;
                    if(i)   dp[i][j][k][l] = std::max(dp[i][j][k][l], dp[i - 1][j][k][l] + a[t]);
                    if(j)   dp[i][j][k][l] = std::max(dp[i][j][k][l], dp[i][j - 1][k][l] + a[t]);
                    if(k)   dp[i][j][k][l] = std::max(dp[i][j][k][l], dp[i][j][k - 1][l] + a[t]);
                    if(l)   dp[i][j][k][l] = std::max(dp[i][j][k][l], dp[i][j][k][l - 1] + a[t]);
                }
            }
        }
    }
    std::cout << dp[cnt[1]][cnt[2]][cnt[3]][cnt[4]] << std::endl;
    return 0;
}