#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <cmath>

using namespace std;
typedef long long ll;
const int N = 810, M = 3100;
const ll inf = 0x3f3f3f3f3f3f3f3f;
int h[N], e[M], ne[M], w[M], idx;
int vis[N][N], C[N];
int n, m, p;

void add(int u, int v, int k){
	e[idx] = v, ne[idx] = h[u], w[idx] = k, h[u] = idx++;
}

struct node{
	int u, maxu;
	ll t, res;
	//默认大根堆, 取相反比较函数变成小根
	bool operator < (const node& x) const {
		return t == x.t ? res < x.res : t > x.t;
	}
};

void dijkstra(){
	memset(vis, 0, sizeof(vis));
	ll ans = 0x3f3f3f3f3f3f3f3f;
	priority_queue<node> q;

	q.push({1, 1, 0ll, (ll)p});
	while(!q.empty()){
		auto now = q.top();
		q.pop();
		int u = now.u, maxu = now.maxu;
		if(vis[u][maxu])
			continue;
		vis[u][maxu] = 1;
		if(u == n)	ans = min(ans, now.t);
		for(int i = h[u]; ~i; i = ne[i]){
			int v = e[i], we = w[i];
			int maxv = (C[v] > C[maxu] ? v : maxu);
			ll t = (ll)ceil((double)max(0ll, we - now.res) / C[maxu]);
			q.push({v, maxv, now.t + t, now.res + t * C[maxu] - we});
		}
	}
	if(ans == inf)
		cout << -1 << '\n';
	else
		cout << ans << '\n';
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	int T;
	cin >> T;

	while(T--) {
		memset(h, -1, sizeof(h));
		idx = 0;
		cin >> n >> m >> p;
		for(int i = 1; i <= n; i++)
			cin >> C[i];
		for(int i = 1; i <= m; i++) {
			int u, v, k;
			cin >> u >> v >> k;
			add(u, v, k);
		}
		dijkstra();
	}
	return 0;
}
