/*
 * Copyright© 2023 lsty. All rights reserved.
 * author: lsty
 * Problem:
 * Tag:
 * Date: 2023-02-27 
 */
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
#include <assert.h>

using namespace std;
const int N = 1e4 + 10;
int n, m, k;
/********************----变量----*************************/
int h[N], e[N << 1], ne[N << 1], w[N << 1], idx;

void add(int x, int y, int z){
	e[idx] = y, ne[idx] = h[x], w[idx] = z, h[x] = idx++;
}
/********************---树的部分---*************************/
int ans = 0;
int root, dis[N], tot;
int siz[N], MinMax;
bool vis[N];
int ways;

/********************---算子树大小, 重心---*************************/
void getsiz(int u, int fa){
	//assert(0);
	siz[u] = 1;
	for(int i = h[u]; ~i; i = ne[i]){
		int v = e[i];
		if(v == fa || vis[v])
			continue;
		getsiz(v, u);
		siz[u] += siz[v];
	}
}

void getroot(int u, int tot, int fa){
	int Maxn = tot - siz[u];
	for(int i = h[u]; ~i; i = ne[i]){
		int v = e[i];
		if(v == fa || vis[v])
			continue;
		getroot(v, tot, u);
		Maxn = max(Maxn, siz[v]);
	}
	Maxn = max(Maxn, tot - siz[u]);
	if(Maxn < MinMax){
		MinMax = Maxn;
		root = u;
	}
}

void getdis(int u, int fa, int d){
	dis[++tot] = d;
	for(int i = h[u]; ~i; i = ne[i]){
		int v = e[i];
		if(v == fa || vis[v])
			continue;
		getdis(v, u, d + w[i]);
	}
}

int work(int u, int d){
	tot = 0;
	getdis(u, 0, d);
	sort(dis + 1, dis + 1 + tot);
	//尺取找有多少对数之和等于 k 
	int uans = 0, i = 1, j = tot;
	while(i < j){
		while(i < j && dis[i] + dis[j] > k)	j--;
		if(dis[i] + dis[j] == k)
			uans++;
		i++;
	}
	return uans;
}

void dfs(int x){
	MinMax = n;
	getsiz(x, 0);
	getroot(x, siz[x], 0);

	ans += work(root, 0);
	//printf("root#%d x#%d\n", root, x);
	
	vis[root] = true;
	for(int i = h[root]; ~i; i = ne[i]){
		int v = e[i];
		if(vis[v])
			continue;
		ans -= work(v, w[i]);
		dfs(v);
	}
}

int main() {
	scanf("%d%d", &n, &m);
	memset(h, -1, sizeof h);
	for(int i = 2; i <= n; i++){
		int x, y, z;
		scanf("%d%d%d", &x, &y, &z);
		add(x, y, z), add(y, x, z);
	}
	for(int i = 1; i <= m; i++){
		memset(vis, 0, sizeof(vis));
		scanf("%d", &k);
		//assert(0);
		ans = 0;
		dfs(1);
		if(ans)
			printf("AYE\n");
		else
			printf("NAY\n");
	}
	return 0;
}