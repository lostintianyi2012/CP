#include <iostream>
#include <algorithm>
#include <string.h>
#include <stdio.h>

const int N = 3e5 + 5;
int n, m, w[N];

/************存图*************/
int h[N], e[N << 1], ne[N << 1], idx;
void add(int x, int y){
    e[idx] = y, ne[idx] = h[x], h[x] = idx++;
}

/***********树链剖分**********/
int dep[N], fa[N], top[N], son[N], siz[N];

void dfs1(int u, int ff){
    fa[u] = ff, dep[u] = dep[ff] + 1, siz[u] = 1;
    for(int i = h[u]; ~i; i = ne[i]){
        int v = e[i];
        if(v == ff)
            continue;
        dfs1(v, u);
        siz[u] += siz[v];
        if(siz[v] > siz[son[u]])
            son[u] = v;
    }
}

void dfs2(int u, int tp){
    top[u] = tp;
    if(!son[u])
        return;

    dfs2(son[u], tp);
    for(int i = h[u]; ~i; i = ne[i]){
        int v = e[i];
        if(v == fa[u] || v == son[u])
            continue;
        dfs2(v, v);
    }
}

int LCA(int x, int y){
    while(top[x] != top[y]){
        if(dep[top[x]] < dep[top[y]])
            std::swap(x, y);
        x = fa[top[x]];
    }
    return dep[x] > dep[y] ? y : x;
}

/************线段树合并***********/
int tot;
int root[N];
struct node{
	int ls, rs, val;
}tr[N * 25];

void insert(int &u, int l, int r, int pos, int k){
	if(!u)	u = ++tot;
	if(l == r){
		tr[u].val += k;
		return ;
	}
	int mid = l + r >> 1;
	if(pos <= mid)	insert(tr[u].ls, l, mid, pos, k);
	else			insert(tr[u].rs, mid + 1, r, pos, k);
	return ;
}

int query(int u, int l, int r, int pos){
	if(!u)
		return 0;
	if(l == r){
		return tr[u].val;
	}
	int mid = l + r >> 1;
	if(pos <= mid)
		return query(tr[u].ls, l, mid, pos);
	else
		return query(tr[u].rs, mid + 1, r, pos);
}

int Merge(int a, int b, int l, int r){
	if(!a || !b)
		return a | b;
	if(l == r){
		tr[a].val += tr[b].val;
		return a;
	}
	int mid = l + r >> 1;
	tr[a].ls = Merge(tr[a].ls, tr[b].ls, l, mid);
	tr[a].rs = Merge(tr[a].rs, tr[b].rs, mid + 1, r);
	return a;
}

int ans[N];

void dfs(int u){
	for(int i = h[u]; ~i; i = ne[i]){
		int v = e[i];
		if(v == fa[u])
			continue;
		dfs(v);
		root[u] = Merge(root[u], root[v], -n, n);
	}
	if(w[u] && dep[u] + w[u] <= n)
		ans[u] += query(root[u], -n, n, dep[u] + w[u]);
	ans[u] += query(root[u], -n, n, dep[u] - w[u]);
}

int main(){
	memset(h, -1, sizeof h);
	scanf("%d%d", &n, &m);
	for(int i = 1; i < n; i++){
		int x, y;
		scanf("%d%d", &x, &y);
		add(x, y), add(y, x);
	}
	dfs1(1, 0), dfs2(1, 1);
	for(int i = 1; i <= n; i++)
		scanf("%d", &w[i]);
	for(int i = 1; i <= m; i++){
		int x, y;
		scanf("%d%d", &x, &y);
		int lca = LCA(x, y);
		insert(root[x], -n, n, dep[x], 1);
		//x关于LCA对称的点的深度
		//假设 x 更深那就是 dep[lca] - (dep[x] - dep[lca])
		//式子化开就可以了
		insert(root[y], -n, n, dep[lca] * 2 - dep[x], 1);
		insert(root[lca], -n, n, dep[x], -1);
		insert(root[fa[lca]], -n, n, dep[lca] * 2 - dep[x], -1);
	}
	dfs(1);
	for(int i = 1; i <= n; i++){
		printf("%d ", ans[i]);
	}
	puts("");
    return 0;
}