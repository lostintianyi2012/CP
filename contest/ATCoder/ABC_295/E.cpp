#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <set>

using namespace std;
typedef long long ll;
const int N = 5555;
const ll mod = 998244353;
int a[N];
int n, m, k;
ll binom[N][N];

ll f_pow(ll a, ll k = mod - 2){
    ll base = 1;
    for(; k; k >>= 1, a = (a * a) % mod){
        if(k & 1)
            base = (base * a) % mod;
    }
    return base;
}

void add(ll &x, ll k){
	x += k;
	if(x > mod)
		x -= mod;
}

int main(){
	for(int i = 0; i < N; i++){
		binom[i][0] = 1;
		for(int j = 1; j <= i; j++)
			binom[i][j] = (binom[i-1][j-1] + binom[i-1][j]) % mod;
	}

	cin >> n >> m >> k;

    for(int i = 1; i <= n; i++){
		cin >> a[i];
	}

	ll ans = 0;

	ll invm = f_pow(m);
	for(int X = 1; X <= m; X++){
		int need = n - k + 1;
		int zeronum = 0;

		for(int j = 1; j <= n; j++){
			if(a[j] >= X)
				need--;
			if(a[j] == 0)
				zeronum++;
		}

		if(need < 0 || need > zeronum){
			add(ans, need < 0 ? 1 : 0);
			continue;
		}

		ll p = (m - X + 1) * invm % mod;
		ll q = ((1 - p) % mod + mod) % mod;
		for(int j = need; j <= zeronum; j++){
			ll k = binom[zeronum][j] * f_pow(p, j) % mod * f_pow(q, zeronum - j) % mod;
			k %= mod;
			add(ans, k);
		}
	}
	printf("%lld\n", ans % mod);
    return 0;
}
