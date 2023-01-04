#include <iostream>
#include <cstdio>
#include <algorithm>
#include <queue>
#include <cstring>

using namespace std;
typedef long long LL;
typedef pair<int, int> PII;

const int N = 1010, M = 100010;
//第0层是原图,第1层是反图
int h[2][N], e[2][M], ne[2][M], w[2][M], idx[2];
int n, m, x;
int dist[2][N];
int st[2][N];

inline void add(int a, int b, int c, int lay){
	int &idxx = idx[lay];
	e[lay][++idxx] = b, ne[lay][idxx] = h[lay][a], w[lay][idxx] = c, h[lay][a] = idxx;
}

void dijkstra(int lay){
	memset(dist[lay], 0x3f, sizeof dist[lay]);
	dist[lay][x] = 0;
	priority_queue<PII, vector<PII>, greater<PII>> heap;
	PII tmp;
	tmp.first = 0, tmp.second = x;
	heap.push(tmp);

	while(heap.size()){
		PII now = heap.top();
		heap.pop();

		int d = now.first, var = now.second;
		if(st[lay][var])
			continue;
		st[lay][var] = true;

		for(int i = h[lay][var]; i; i = ne[lay][i]){
			int j = e[lay][i];
			if(dist[lay][j] > d + w[lay][i]){
				dist[lay][j] = d + w[lay][i];
				PII tmp;
				tmp.first = dist[lay][j], tmp.second = j;
				heap.push(tmp);
			}
		}
	}
}

int main(){
	//freopen("tmp.in", "r", stdin);
	//freopen("tmp.out", "w", stdout);
	scanf("%d%d%d", &n, &m, &x);
	for(int i = 1; i <= m; i++)
	{
		int a, b, c;
		scanf("%d%d%d", &a, &b, &c);
		add(a, b, c, 0), add(b, a, c, 1);
	}
	//在原图和反图分别跑一次dijkstra
	dijkstra(0), dijkstra(1);

	int ans = 0;
	for(int i = 1; i <= n; i++)
		ans = max(ans, dist[0][i] + dist[1][i]);

	printf("%d\n", ans);
	return 0;
}
