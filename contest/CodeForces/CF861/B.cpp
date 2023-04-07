#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstdio>
#include <vector>

using namespace std;
typedef long long ll;
const int N = 4e5 + 10;
int n, m;
vector<ll> a[N], pre[N];

char gc(){
	static char buf[1 << 16], *p1, *p2;
	if(p1 == p2)
		p2 = (p1 = buf) + fread(buf, 1, 1 << 16, stdin);
	return p1 == p2 ? EOF : *p1++;
}

ll read(){
	ll s = 0, f = 1;
	char c = gc();
	while(!isdigit(c)){
		if(c == '-')
			f = -1;
		c = gc();
	}
	while(isdigit(c)){
		s = (s << 3) + (s << 1) + (c ^ 48);
		c = gc();
	}
	return s * f;
}

void write(ll x){
	static int stk[50];
	if(x == 0){
		putchar('0');
		return ;
	}
	int tt = 0;
	while(x){
		stk[tt++] = x % 10;
		x /= 10;
	}
	while(tt){
		putchar(stk[--tt] + '0');
	}
}

int main(){
	int T;
	T = read();
	while(T--){
		n = read(), m = read();
        for(int i = 1; i <= m; i++)
            a[i].resize(n + 1), pre[i].resize(n + 1);
        for(int i = 1; i <= n; i++){
            for(int j = 1; j <= m; j++)
                a[j][i] = read();
        }
        for(int i = 1; i <= m; i++)
            sort(a[i].begin() + 1, a[i].end());
        for(int i = 1; i <= m; i++){
            for(int j = 1; j <= n; j++)
                pre[i][j] = pre[i][j-1] + a[i][j];
        }
        ll ans = 0;
        for(int i = 1; i <= m; i++){
            for(int j = 1; j <= n; j++){
                ans += (a[i][j] * (j-1) - pre[i][j-1]) + (pre[i][n] - pre[i][j] - a[i][j] * (n - j));
            }
        }
		write(ans >> 1);
		putchar('\n');
		for(int i = 1; i <= m; i++)
			a[i].clear(), pre[i].clear();
	}
	return 0;
}
