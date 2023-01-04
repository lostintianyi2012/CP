#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>

using namespace std;
typedef pair<int,int> PII;

const int N = 1e6 + 10, M = 4e6 + 10, mod = 100003;
int h[N], ne[M], e[M], w[M], idx;
int n, m;
int cnt[N], dist[N];
bool vis[N];

inline void add(int a, int b){
	e[idx] = b, ne[idx] = h[a], w[idx] = 1, h[a] = idx++;
}

void dijkstra(){
	memset(dist, 0x3f, sizeof dist);
	priority_queue<PII, vector<PII>, greater<PII>> heap;
	cnt[1] = 1, dist[1] = 0;
	heap.push({0, 1});

	while(!heap.empty()){
		PII u = heap.top();
		heap.pop();

		int ver = u.second, d = u.first;
		if(vis[ver])
			continue;
		vis[ver] = true;

		for(int i = h[ver]; ~i; i = ne[i]){
			int j = e[i];

			if(dist[j] > dist[ver] + w[i]){
				dist[j] = dist[ver] + w[i];
				cnt[j] = cnt[ver];
				heap.push({dist[j], j});
			}

			else if(dist[j] == dist[ver] + w[i]){
				cnt[j] += cnt[ver];
				cnt[j] %= mod;
			}
		}
	}
}

int main(){
	memset(h, -1, sizeof h);
	scanf("%d%d", &n, &m);
	for(int i = 0; i < m; i++){
		int a, b;
		scanf("%d%d", &a, &b);
		add(a, b), add(b, a);
	}
	dijkstra();
	for(int i = 1; i <= n; i++){
		printf("%d\n", cnt[i]);
	}

	return 0;
}
