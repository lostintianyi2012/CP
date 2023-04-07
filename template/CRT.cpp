#include <iostream>
#include <algorithm>
#include <math.h>

typedef long long ll;
const int N = 12;
ll a[N], m[N], Mi[N], M = 1, X = 0;
ll n;

char buf[1 << 20], *p1, *p2;
inline char gc(){
	if(p1 == p2){
		p2 = (p1 = buf) + fread(buf, 1, 1 << 20, stdin);
	}
	return p1 == p2 ? EOF : *p1++;
}

ll read(){
	int w = 1;
	ll s = 0;
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
	return s *= w;
}

void exgcd(ll a, ll b, ll &d, ll &x, ll &y){
	if(b == 0){
		d = a;
		x = 1, y = 0;
		return ;
	}
	exgcd(b, a % b, d, y, x);
	y -= a / b * x;
}

int main(){
	n = read();
	for(int i = 1; i <= n; i++){
		m[i] = read();
		a[i] = read();
		M *= m[i];
	}
	for(int i = 1; i <= n; i++){
		Mi[i] = M / m[i];
		ll x = 0, y = 0;
		ll d;
		exgcd(Mi[i], m[i], d, x, y);
		X += a[i] * Mi[i] * (x < 0 ? x + m[i] : x);
	}
	printf("%lld\n", X % M);
	return 0;
}
