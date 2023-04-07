#include <iostream>
#include <algorithm>
#include <string.h>

typedef long long ll;
const int N = 1e6 + 10;
const long long mod = 1e9 + 7;
int n, m;
int c[N];
int pre[N], suf[N];

/*==============Fast IO===============*/
char buf[1 << 20], *p1, *p2;

char gc(){
	//p2为段尾, p1为段头
	if(p1 == p2)
		p2 = (p1 = buf) + fread(buf, 1, 1 << 20, stdin);
	//如果读完了(加上剩余长度仍然p1 == p2代表剩下为空)
	//返回 EOF, 否则返回当前这一位字符
	return p1 == p2 ? EOF : *p1++;
}

inline int read(){
	int s = 0, w = 1;
	char c = gc();
	while(!isdigit(c)){
		if(c == '-')
			w = -1;
		c = gc();
	}
	while(isdigit(c)){
		s = (s << 3) + (s << 1) + (c ^ 48);
		c = gc();
	}
	return s * w;
}
/*====================================*/

ll f_pow(ll a, int k){
	ll base = 1;
	for(; k; k >>= 1, a = (a * a) % mod){
		if(k & 1){
			base = (base * a) % mod;
		}
	}
	return base;
}

ll fac(ll k){
	ll base = 1;
	for(int i = 1; i <= k; i++)
		base = base * i % mod;
	return base;
}

ll inv(ll k){
	return f_pow(k, mod - 2);
}

ll C(ll n, ll m){
	return fac(n) * inv(fac(m)) % mod * inv(fac(n-m)) % mod;
}

int main(){
	n = read(), m = read();
	for(int i = 1; i <= m; i++){
		c[i] = read();
		n -= c[i] + 1;
	}
	printf("%lld\n", C(n + m - 1, m - 1));
	return 0;
}
