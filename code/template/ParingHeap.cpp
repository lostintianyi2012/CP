#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string.h>

const int N = 1e5 + 3, M = 2e5 + 3;

struct H{
    int child, fa, sibling;
	int val;
} heap[N];

int root, h[N], e[M], ne[M], w[M], dis[N], idx;
bool add_to_heap[N], st[N]; // add_to_heap记录每个点是否被加入堆，f记录是否被删除
int n, m, start;

void add(int u, int v, int c){
	e[++idx] = v, ne[idx] = h[u], w[idx] = c, h[u] = idx;
}

int meld(int x, int y)
{
    if (!x || !y)
        return x | y;
    if (dis[x] > dis[y])
        std::swap(x, y);
    heap[y].fa = x;
    heap[y].sibling = heap[x].child;
    heap[heap[y].sibling].fa = y;
    heap[x].child = y;
    return x;
}

int merge(int x)
{
	heap[x].fa = 0;
    if (!x || !heap[x].sibling)
        return x;
    int a = heap[x].sibling, add_to_heap = heap[a].sibling;
	//清空已经合并的
	heap[x].sibling = heap[a].sibling = heap[a].fa = 0;
    return meld(meld(x, a), merge(add_to_heap));
}

void decrease_key(int x, int v)
{ // 插入/修改
    if (dis[x] = v, !add_to_heap[x]){
        add_to_heap[x] = 1;
		root = meld(root, x);
		return ;
	}
    if (!heap[x].fa)
        return;
    if (heap[heap[x].fa].child == x)
        heap[heap[x].fa].child = heap[x].sibling;
    else
        heap[heap[x].fa].sibling = heap[x].sibling;

    heap[heap[x].sibling].fa = heap[x].fa;
	heap[x].fa = heap[x].sibling = 0;
	root = meld(root, x);
}

void dijkstra(){
	memset(dis, 0x3f, sizeof dis);
	decrease_key(start, 0);
	while(!st[root]){
		int u = root;
		st[root] = true;
	}
}

int main(){
    scanf("%d%d%d", &n, &m, &start);
    for (int i = 1; i <= m; i++){
		int u, v, c;
        scanf("%d%d%d", &u, &v, &c);
		add(u, v, c);
	}

    for (int i = 1; i <= n; ++i)
        printf("%d ", dis[i]);
    return 0;
}