#include <iostream>
#include <string.h>
#include <algorithm>
#include <stdio.h>

using namespace std;
typedef unsigned long long ull;
const int N = 20, mod = 1e9 + 7;
//sum[i]表示后 i 位的答案
long long dp[N];
int a[N];

long long f_pow(int a, int k){
	long long base = 1;
	for(; k; k >>= 1, a *= a){
		if(k & 1){
			base *= a;
			base %= mod;
		}
	}
	return base;
}

long long dfs(int u, bool lim){
	if(u == 0)
		return 0;
	if(!lim && dp[u] != -1)
		return dp[u];
	int maxn = lim ? a[u] : 9;
	long long ans = 0;
	for(int i = 0; i <= maxn; i++){
		ans += dfs(u-1, lim && (i == maxn)); 
		ans += (i * f_pow(10, u-1)) % mod;
		ans %= mod;
	}

	if(!lim)
		dp[u] = ans;
	return ans;
}

long long work(ull x){
	int idx = 0;
	while(x){
		a[++idx] = x % 10;
		x /= 10;
	}
	return dfs(idx, true);
}

int main(){
	memset(dp, -1, sizeof dp);
	int T;
	scanf("%d", &T);
	while(T--){
		ull l, r;
		scanf("%llu%llu", &l, &r);
		printf("%lld\n", (((work(r) - work(l - 1)) % mod) + mod) % mod);
	}
	return 0;
}
