#include <iostream>
#include <algorithm>
#include <string.h>
#include <stdio.h>

typedef long long ll;
const int mod = 998244353;
ll n, k;

ll f_pow(ll a, ll k){
	ll base = 1;
	for(; k; k >>= 1, a *= a){
		a %= mod;
		if(k & 1){
			base *= a;
			base %= mod;
		}
	}
	return base;
}

int main(){
	scanf("%lld%lld", &n, &k);
	printf("%lld\n", f_pow(f_pow(2, k) - 1, n));
	return 0;
}