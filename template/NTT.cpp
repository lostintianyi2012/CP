#include <iostream>
#include <string.h>
#include <algorithm>
#include <math.h>

typedef long long ll;
const int maxn = 1 << 22;
const int g = 3, gi = 332748118, mod = 998244353;

int n, m, rev[maxn];
ll a[maxn], b[maxn];
ll f_pow(ll a, ll k){
	ll res = 1;
	for(; k; k >>= 1, a *= a){
		a %= mod;
		if(k & 1)
			res = res * a % mod;
	}
	return res;
}

void NTT(ll *a, int n, int inv){
	for(int i = 0; i < n; i++)
		if(i < rev[i])
			std::swap(a[i], a[rev[i]]);

	for(int i = 1; i < n; i <<= 1){
		ll gn = f_pow(inv ? g : gi, (mod - 1) / (i << 1));

		for(int j = 0; j < n; j += (i << 1)){
			ll g0 = 1;
			for(int k = 0; k < i; k++, g0 = g0 * gn % mod){
				ll x = a[j + k], y = g0 * a[i + j + k] % mod;
				a[j + k] = (x + y) % mod;
				a[i + j + k] = (x - y + mod) % mod;
			}
		}
	}
}

int main(){
	scanf("%d%d", &n, &m);
	for(int i = 0; i <= n; i++)
		scanf("%lld", &a[i]);
	for(int i = 0; i <= m; i++)
		scanf("%lld", &b[i]);
	int k = std::max((int)ceil(log2(n+m)), 1);
	int len = 1 << k;
	for(int i = 0; i < len; i++)
		rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (k - 1));
	NTT(a, len, 1);
	NTT(b, len, 1);
	for(int i = 0; i <= len; i++)
		a[i] = a[i] * b[i] % mod;
	NTT(a, len, 0);
	ll inv = f_pow(len, mod - 2);
	for(int i = 0; i <= n + m; i++){
		printf("%lld ", a[i] * inv % mod);
	}
	return 0;
}
