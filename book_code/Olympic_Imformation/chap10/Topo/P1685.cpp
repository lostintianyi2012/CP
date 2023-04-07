#include <iostream>
#include <queue>
#include <string.h>
#include <algorithm>

using namespace std;
const int N = 1e4 + 10, M = 5e4 + 10;
const int mod = 1e4;
int h[N], e[M], ne[M], w[M], idx;
int dp[N];
int ways[N];
int n, m, st, ed, t;
int ans;
int in[N];
void add(int x, int y, int z){
	e[idx] = y, ne[idx] = h[x], w[idx] = z, h[x] = idx++;
}

void bfs(int st){
	queue<int> q;
	for(int i = 1; i <= n; i++)
		if(in[i] == 0)
			q.push(i), ways[i] = 1;
	while(!q.empty()){
		int u = q.front();
		q.pop();
		for(int i = h[u]; ~i; i = ne[i]){
			int v = e[i];

			dp[v] = (ways[u] * w[i] + dp[v] + dp[u]) % mod;
			ways[v] = (ways[u] + ways[v]) % mod;

			in[v]--;
			if(in[v] == 0)
				q.push(v);
		}
	}
}

int main(){
	memset(h, -1, sizeof h);
	scanf("%d%d%d%d%d", &n, &m, &st, &ed, &t);
	for(int i = 1; i <= m; i++){
		int x, y, z;
		scanf("%d%d%d", &x, &y, &z);
		add(x, y, z);
		in[y]++;
	}
	bfs(st);

//	printf("%d\n", ways[ed]);
//	for(int i = 1; i <= n; i++){
//		printf("dp[%d]: %d\n", i, dp[i]);
//	}	
	
	int k = (t * (ways[ed] - 1)) % mod;
	printf("%d\n", (dp[ed] + k) % mod);
	return 0;
}
