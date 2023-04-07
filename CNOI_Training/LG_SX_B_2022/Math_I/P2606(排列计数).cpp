#include <iostream>
#include <string.h>
#include <algorithm>
#include <stdio.h>

typedef long long ll;
const int N = 1e6 + 10;
ll fac[N];
ll siz[N];
ll dp[N];
int n;
ll m;

ll inv(ll a, int k = m - 2){
	ll base = 1;
	for(; k; k >>= 1, a = (a * a) % m){
		if(k & 1){
			base = (base * a) % m;
		}
	}
	return base;
}

ll C(int a, int b){
	return fac[a] % m * inv(fac[b]) % m * inv(fac[a-b]) % m;
}

ll Lucas(int a, int b){
	if(a < m && b < m)
		return C(a, b);
	return C(a % m, b % m) * Lucas(a / m, b / m) % m;
}

void dfs1(int u){
	if(u > n)
		return ;
	siz[u] = 1;
	for(int i = 0; i < 2; i++){
		dfs1(u << 1 | i);
		siz[u] += siz[u << 1 | i];
	}
}

ll dfs(int u){
	if(u > n)
		return 1;
	return Lucas(siz[u] - 1, siz[u << 1]) * dfs(u << 1) % m * dfs(u << 1 | 1) % m;
}

int main(){
	scanf("%d%lld", &n, &m);
	
	dfs1(1);

	fac[0] = 1;
	for(int i = 1; i <= n; i++)
		fac[i] = fac[i-1] * i % m;

	printf("%lld\n", dfs(1));
	return 0;
}
