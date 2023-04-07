#include <iostream>
#include <algorithm>
#include <string.h>
#include <algorithm>

typedef long long ll;
const int N = 2e5 + 5e4;
const ll mod = 1e9 + 7;
int a[N];
ll f[N];
int n;

char buf[1 << 20], *p1, *p2;
inline char gc(){
	if(p1 == p2){
		p2 = (p1 = buf) + fread(buf, 1, 1 << 20, stdin);
	}
	return p1 == p2 ? EOF : *p1++;
}

inline ll read(){
	ll s = 0, w = 1;
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

int main(){
	n = read();
	for(int i = 1; i <= n; i++)
		a[i] = read();

	ll ans = 0;
	for(int i = 1; i <= n; i++){
		for(int S = (a[i] - 1) & a[i]; S; S = (S - 1) & a[i])
			f[S] = (f[S] + f[a[i]] + 1) % mod;
		ans = (ans + f[a[i]]) % mod;
	}
	printf("%lld\n", ans);
	return 0;
}
