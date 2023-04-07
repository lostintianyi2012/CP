#include <iostream>
#include <string.h>
#include <algorithm>
#include <stdio.h>
#include <vector>
#include <queue>

using namespace std;
const int N = 1e5 + 10;
int h[N], e[N], ne[N], idx;
int ans[N];
int tot;
int in[N];
int n, m;

void add(int x, int y){
	e[idx] = y, ne[idx] = h[x], h[x] = idx++;
}

void bfs(){
	priority_queue<int, vector<int>, less<int> > heap;

	for(int i = 1; i <= n; i++)
		if(!in[i])
			heap.push(i);

	while(!heap.empty()){
		int u = heap.top();
		heap.pop();
		ans[++tot] = u;

		for(int i = h[u]; ~i; i = ne[i]){
			int v = e[i];
			in[v]--;
			if(!in[v])
				heap.push(v);
		}
	}
}

int main(){
	int T;
	scanf("%d", &T);
	while(T--){
		memset(h, -1, sizeof(h));
		memset(in, 0, sizeof(in));

		idx = 0, tot = 0;
		scanf("%d%d", &n, &m);
		bool flag = false;
		for(int i = 0; i < m; i++){
			int x, y;
			scanf("%d%d", &x, &y);
			add(y, x);
			in[x]++;
			if(x == y)
				flag = true;
		}
		bfs();
		if(tot ^ n || flag)
			printf("Impossible!");
		else
			for(int i = n; i >= 1; i--)
				printf("%d ", ans[i]);
		printf("\n");
	}
	return 0;
}
