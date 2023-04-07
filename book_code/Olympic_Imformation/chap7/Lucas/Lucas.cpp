#include <iostream>
#include <string.h>
#include <stdio.h>

using namespace std;
typedef long long ll;

const int N = 1e5 + 10;
int n, m, p;
int T;
ll fac[N], inv_fac[N];

ll f_pow(ll a, ll k){
	ll base = 1;
	for(; k; k >>= 1, a = (a * a) % p){
		if(k & 1){
			base = (base * a) % p;
		}
	}
	return base;
}

void factory(){
	fac[0] = 1;
	for(int i = 1; i < p; i++)
		fac[i] = (fac[i-1] * i) % p;

	inv_fac[p - 1] = f_pow(fac[p - 1], p - 2);

	for(int i = p - 2; i >= 0; i--)
		inv_fac[i] = (inv_fac[i + 1] * (i + 1)) % (ll)p;
}

int C(int n, int m){
	if(n > m)
		return 0;
	return fac[m] * inv_fac[n] % p * inv_fac[m - n] % p;
}

ll Lucas(int n, int m){
	if(n < p && m < p){
		return C(n, m);
	}
		
	return C(n % p, m % p) * C(n / p, m / p) % p;
}

int main(){
	scanf("%d", &T);
	while(T--){
		scanf("%d%d%d", &n, &m, &p);
		factory();
		printf("%lld\n", Lucas(n, n + m));
	}
	return 0;
}
