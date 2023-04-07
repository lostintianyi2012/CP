#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>

using namespace std;
typedef long long ll;
const int N = 5e5 + 10;

/*=======Fast IO========*/
inline char gc(){
	static char buf[1 << 20], *p1, *p2;
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
		s = (s << 3) + (s << 1) +(c ^ 48);
		c = gc();
	}
	return s * w;
}

inline void write(ll x){
	static int stk[35];
	int tt = 0;
	if(x < 0)	putchar('-'), x = -x;
	do{
		stk[tt++] = x % 10, x /= 10;
	}while(x);
	while(tt)
		putchar(stk[--tt] + '0');
}

int main(){
	return 0;
}
