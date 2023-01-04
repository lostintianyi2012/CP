#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 210, M = 10050, inf = 0x3f3f3f3f;
int n, m, S, T;
int h[N], e[M], ne[M], w[M], idx;
//the array pre contains the precursor of this node
int q[N], d[N], pre[N];
bool st[N];

inline void add(int a, int b, int c){
	e[idx] = b, ne[idx] = h[a], w[idx] = c, h[a] = idx++;
}

bool bfs(){
	int hh = 0, tt = 0;
	memset(st, false, sizeof st);
	q[0] = S, st[S] = true, d[S] = inf;
	while(hh <= tt){
		int t = q[hh++];

		for(int i = h[t]; ~i; i = ne[i]){
			int ver = e[i];
			//没有被访问过并且还有残余流量
			if(!st[ver] && w[i]){
				st[ver] = true;
				d[ver] = min(d[t], w[i]);
				pre[ver] = i;

				if(ver == T)
					return true;

				q[++tt] = ver;
			}
		}
	}
	return false;
}

int ek(){
	int r = 0;
	while(bfs()){
		r += d[T];
		for(int i = T; i != S; i = e[pre[i] ^ 1]){
			//w[pre[i] ^ 1] 保存可以撤销多少流量，因为不能撤销多余走过的流量的流量
			w[pre[i]] -= d[T], w[pre[i] ^ 1] += d[T];
		}
	}
	return r;
}

signed main(){
	scanf("%lld%lld%lld%lld", &n, &m, &S, &T);
	memset(h, -1, sizeof h);
	while(m--){
		static int a, b, c;
		scanf("%lld%lld%lld", &a, &b, &c);
		add(a, b, c), add(b, a, 0);
	}

	printf("%lld\n", ek());
	return 0;
}
