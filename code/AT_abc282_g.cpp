#include <bits/stdc++.h>

using namespace std;
const int N = 105;
long long dp[N][N][N][N];
long long sum[N][N], ans;
int n, k;
int p;

int main(){
    scanf("%d%d%d", &n, &k, &p);
    dp[1][0][1][1] = 1;

    for(int i = 2; i <= n; i++){
        for(int j = 0; j < i - 1; j++){
            memset(sum, 0, sizeof(sum));

            for(int a = 1; a < i; a++){
                for(int b = 1; b < i; b++){
                    sum[a][b] = (sum[a-1][b] + sum[a][b-1] - sum[a-1][b-1] + dp[i-1][j][a][b]) % p;
                    sum[a][b] = (sum[a][b] + p) % p;
                }
            }

            for(int a = 1; a <= i; a++){
                for(int b = 1; b <= i; b++){
                    dp[i][j][a][b] = (dp[i][j][a][b] + sum[i-1][b-1] - sum[a-1][b-1] + sum[a-1][i-1] - sum[a-1][b-1]) % p;
                    dp[i][j][a][b] = (dp[i][j][a][b] + p) % p;
                }
            }

            for(int a = 1; a <= i; a++){
                for(int b = 1; b <= i; b++){
                    dp[i][j+1][a][b] = (dp[i][j+1][a][b] + sum[a-1][b-1] + sum[i-1][i-1] - sum[a-1][i-1] - sum[i-1][b-1] + sum[a-1][b-1]) % p;
                    dp[i][j+1][a][b] = (dp[i][j+1][a][b] + p) % p;
                }
            }
        }
    }

    for(int i = 1; i <= n; i ++){
        for(int j = 1; j <= n; j ++){
            ans = (ans + dp[n][k][i][j]) % p;
        }
    }

    printf("%lld\n", ans);
    return 0;
}