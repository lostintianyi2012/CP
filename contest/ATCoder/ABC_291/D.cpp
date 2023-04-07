#include <iostream>
#include <string.h>
#include <algorithm>
#include <stdio.h>

typedef long long ll;
const int N = 2e5 + 10;
const ll mod = 998244353;
int card[2][N];
//dp[0][i]表示前 i 张牌, 第 i 张牌正面朝上，反之亦然
ll dp[2][N];
int n;

int main(){
	scanf("%d", &n);
	dp[0][1] = 1, dp[1][1] = 1;
	for(int i = 1; i <= n; i++)
		scanf("%d%d", &card[0][i], &card[1][i]);

	for(int i = 2; i <= n; i++){
		if(card[0][i] != card[0][i-1]){
			dp[0][i] += dp[0][i-1];
		}
		if(card[0][i] != card[1][i-1]){
			dp[0][i] += dp[1][i-1];
		}
		dp[0][i] %= mod;
		if(card[1][i] != card[0][i-1]){
			dp[1][i] += dp[0][i-1];
		}
		if(card[1][i] != card[1][i-1]){
			dp[1][i] += dp[1][i-1];
		}
		dp[1][i] %= mod;
	}
	printf("%lld\n", (dp[0][n] + dp[1][n]) % mod);
	return 0;
}
