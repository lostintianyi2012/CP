#include <iostream>
#include <algorithm>
#include <stack>
#include <string.h>
#include <stdio.h>
#include <queue>

using namespace std;
const int N = 2e5 + 10;
int fa[N];
int h[N], e[N], ne[N], idx;
int n, m;
int in[N];
bool st[N];
bool flag = true;
stack<int> stk;
int ans[N];

void add(int u, int v){
	e[idx] = v, ne[idx] = h[u], h[u] = idx++;
}

int color[N];
int nxt[N], len[N];
void dfs0(int u){
	len[u] = 1;
	color[u] = 0;

	for(int i = h[u]; ~i; i = ne[i]){
		int v = e[i];
		if(color[v] == 0){
			flag = false;
			return ;
		}
		if(color[v] == -1)
			dfs0(v);

		if(flag == false)
			return ;

		if(nxt[u] == -1 || len[v] > len[nxt[u]]){
			nxt[u] = v;
		}
	}
	color[u] = 1;
	if(nxt[u] != -1)
		len[u] = len[nxt[u]] + 1;
}

void dfs(int u){
	if(flag == false)
		return ;

	if(st[u]){
		flag = false;
	}
	st[u] = true;
	stk.push(u);

	if(nxt[u] == -1){
		return ;
	}
	int v = nxt[u];
	dfs(v);
}

int main(){
	memset(h, -1, sizeof h);
	memset(color, -1, sizeof color);
	memset(nxt, -1, sizeof nxt);
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= m; i++){
		int x, y;
		scanf("%d %d", &x, &y);
		add(y, x);
		in[x]++;
	}
	for(int i = 1; i <= n; i++){
		if(in[i] == 0){
			dfs0(i);
			dfs(i);
			break;
		}
	}
	for(int i = 1; i <= n; i++){
		if(!st[i]){
			flag = false;
			break;
		}
	}

	if(flag){
		puts("Yes");
		for(int i = 1; i <= n; i++){
			ans[stk.top()] = i;
			stk.pop();
		}
		for(int i = 1; i <= n; i++){
			printf("%d ", ans[i]);
		}
	}
	else{
		puts("No");
	}
	return 0;
}

