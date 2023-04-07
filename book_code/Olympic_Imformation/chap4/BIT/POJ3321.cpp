#pragma GCC optimize(2)
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;
typedef pair<int, int> pii;
const int N = 2e5 + 10;
pii subtree[N];
int a[N], tr[N];
int id[N], cur;

int h[N], e[N], ne[N], idx;
int n, m;

inline void add(int x, int y){
	e[idx] = y, ne[idx] = h[x], h[x] = idx++;
}

void dfs(int u, int fa){
	id[u] = ++cur;
	subtree[u].first = cur;
	for(int i = h[u]; ~i; i = ne[i]){
		int v = e[i];
		if(v == fa)
			continue;
		dfs(v, u);
	}
	subtree[u].second = cur;
}

inline int lowbit(int x){
	return x & -x;
}

inline void tadd(int x, int k){
	for(int i = x; i <= n; i += lowbit(i))
		tr[i] += k;
}

inline int query(int x){
	int ans = 0;
	for(int i = x; i > 0; i -= lowbit(i))
		ans += tr[i];
	return ans;
}

int main(){
	while(scanf("%d", &n) != EOF){
		memset(h, -1, sizeof h);
		for(int i = 1; i < n; i++){
			int x, y;
			scanf("%d%d", &x, &y);
			add(x, y), add(y, x);
		}
		dfs(1, 0);
		scanf("%d", &m);
		char op[2];
		for(int i = 1; i <= n; i++)
			a[i] = 1, tadd(i, a[i]);

		for(int i = 1; i <= m; i++){
			scanf("%s", op);
			if(op[0] == 'C'){
				int x;
				scanf("%d", &x);
				tadd(id[x], -a[id[x]]);
				a[id[x]] ^= 1;
				tadd(id[x], a[id[x]]);
			}
			else{
				int x;
				scanf("%d", &x);
				printf("%d\n", query(subtree[x].second) - query(subtree[x].first - 1));
			}
		}
	}
	return 0;
}
