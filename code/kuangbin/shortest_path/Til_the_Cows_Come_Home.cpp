#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdio>
#include <queue>

using namespace std;
const int N = 1010, M = 4010;
int h[N], e[M], ne[M], w[M], idx;
int dist[N];
bool st[N];
int n, m;

inline void add(int a, int b, int c){
	e[++idx] = b, ne[idx] = h[a], w[idx] = c, h[a] = idx;
}

void spfa(){
	memset(dist, 0x3f, sizeof dist);
	queue<int> q;
	q.push(1);
	dist[1] = 0;
	st[1] = true;
	
	while(!q.empty()){
		int now = q.front();
		q.pop();
		st[now] = false;

		for(int i = h[now]; i; i = ne[i]){
			int j = e[i];
			if(dist[j] > dist[now] + w[i]){
				dist[j] = dist[now] + w[i];

				if(!st[j]){
					q.push(j);
					st[j] = true;
				}
			}
		}
	}
}



int main(){
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= m; i++){
		int a, b, c;
		scanf("%d%d%d", &a, &b, &c);
		add(a, b, c), add(b, a, c);
	}
	spfa();
	printf("%d\n", dist[n]);
	return 0;
}
