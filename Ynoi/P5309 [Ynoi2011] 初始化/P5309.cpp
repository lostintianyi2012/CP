#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdio>
#include <cmath>

using namespace std;
typedef long long ll;
const int N = 2e5 + 10, mod = 1000000007;
const int M = 5e2 + 10;

/*===========Fast IO===========*/
inline char gc(){
	static char buf[1 << 22], *p1, *p2;
	if(p1 == p2){
		p2 = (p1 = buf) + fread(buf, 1, 1 << 22, stdin);
	}
	return p1 == p2 ? EOF : *p1++;
}

inline int read(){
	int s = 0;
	char c = gc();
	while(!isdigit(c))
		c = gc();
	
	while(isdigit(c)){
		s = s * 10 +(c ^ 48);
		c = gc();
	}
	return s;
}

char pbuf[1 << 20], *outp = pbuf;
inline void push(const char& x){
	if(outp - pbuf == 1 << 20)
		fwrite(pbuf, 1, 1 << 20, stdout), outp = pbuf;
	*outp++ = x;
}

inline void write(int x){
	static int stk[35];
	int tt = 0;
	do{
		stk[tt++] = x % 10, x /= 10;
	}while(x);
	while(tt)
		push(stk[--tt] + '0');
	push('\n');
}
int n, m;
int a[N];

int pos[N], bl[M], br[M], blocknum;
int pre[M][M], suf[M][M], sum[N];
int block;

inline void add(int &x, int y){
	x += y;
	if(x > mod)
		x -= mod;
}

inline void minu(int &x, int y){
	x -= y;
	if(x < 0)
		x += mod;
}

void block_init(){
	blocknum = n / block;
	if(n % block)	blocknum++;
	for(int i = 1; i <= blocknum; i++)
		bl[i] = br[i-1] + 1, br[i] = br[i-1] + block;
	br[blocknum] = n;
	for(int i = 1; i <= n; i++)
		pos[i] = (i-1) / block + 1;
	for(int i = 1; i <= n; i++)
		add(sum[pos[i]], a[i]);
}

inline void modify(int x, int y, int z){
	if(x >= block){
		for(int i = y; i <= n; i += x)
			add(a[i], z), add(sum[pos[i]], z);
	}
	else{
		for(int i = y; i <= x; i++)
			add(pre[x][i], z);
		for(int i = 1; i <= y; i++)
			add(suf[x][i], z);
	}
}

inline int blocksum(int l, int r){
	int posl = pos[l], posr = pos[r];
	int ans = 0;
	if(posl == posr){
		for(int i = l; i <= r; i++)
			add(ans, a[i]);
	}
	else{
		for(int i = posl + 1; i <= posr - 1; i++)
			add(ans, sum[i]);
		for(int i = l; i <= br[posl]; i++)
			add(ans, a[i]);
		for(int i = bl[posr]; i <= r; i++)
			add(ans, a[i]);
	}
	return ans;
}

inline int query(int l, int r){
	int Bsum = blocksum(l, r);
	for(int i = 1; i < block; i++){
		if(!pre[i][i])
			continue;
		int L = (l - 1) / i + 1, R = (r - 1) / i + 1;
		if(L == R){
			minu(Bsum, pre[i][(l-1) % i]);
			add(Bsum, pre[i][(r-1) % i + 1]);
		}
		else{
			add(Bsum, 1ll * (R - L - 1) * pre[i][i] % mod);
			add(Bsum, pre[i][(r-1) % i + 1]);
			add(Bsum, suf[i][(l-1) % i + 1]);
		}
	}
	return Bsum;
}

int main(){
	n = read();
	m = read();
	for(int i = 1; i <= n; i++)
		a[i] = read();
	block = sqrt(n);
	block_init();

	for(int i = 1; i <= m; i++){
		int op = read();
		if(op == 1){
			static int x, y, z;
			x = read(), y = read(), z = read();
			modify(x, y, z);
		}
		else{
			int l = read(), r = read();
			write(query(l, r));
		}
	}
	fwrite(pbuf, 1, outp - pbuf, stdout);
	return 0;
}
