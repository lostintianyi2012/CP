#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;
typedef long long ll;
const int N = 5e5 + 10, inf = 0x3f3f3f3f;
ll a[N], b[N];
int n, m;

struct node{
	int l, r;
	ll lmax, rmax;
	ll amax, bmin;
	ll ans;
	node(){
		l = r = 0;
		lmax = -inf, rmax = -inf;
		ans = -inf;
	}
}tr[N << 2];

void pushup(node& root, const node& ls, const node& rs){
	root.amax = max(ls.amax, rs.amax);
	root.bmin = min(ls.bmin, rs.bmin);
	root.lmax = ls.amax - rs.bmin;
	root.rmax = rs.amax - ls.bmin;
	root.lmax = max(root.lmax, max(ls.lmax, rs.lmax));
	root.rmax = max(root.rmax, max(ls.rmax, rs.rmax));
	root.ans = max(max(ls.lmax + rs.amax, rs.rmax + ls.amax), max(ls.ans, rs.ans));
}

void build(int u, int l, int r){
	tr[u].l = l, tr[u].r = r;
	if(l == r){
		tr[u].amax = a[l];
		tr[u].bmin = b[l];
		tr[u].lmax = -inf;
		tr[u].rmax = -inf;
		tr[u].ans = -inf;
		return ;
	}
	int mid = l + r >> 1;
	build(u << 1, l, mid);
	build(u << 1 | 1, mid + 1, r);
	pushup(tr[u], tr[u << 1], tr[u << 1 | 1]);
}

void modify(int u, int x, int v, int type){
	if(tr[u].l == x && tr[u].r == x){
		if(type == 0)
			tr[u].amax = v;
		else
			tr[u].bmin = v;
		return ;
	}
	int mid = tr[u].l + tr[u].r >> 1;
	if(x <= mid)
		modify(u << 1, x, v, type);
	else
		modify(u << 1 | 1, x, v, type);
	pushup(tr[u], tr[u << 1], tr[u << 1 | 1]);
}

node query(int u, int l, int r){
	if(l <= tr[u].l && tr[u].r <= r){
		return tr[u];
	}
	int mid = tr[u].l + tr[u].r >> 1;
	if(r <= mid)	return query(u << 1, l, r);
	else if(l > mid)	return query(u << 1 | 1, l, r);
	else{
		node res;
		node ls = query(u << 1, l, r);
		node rs = query(u << 1 | 1, l, r);
		pushup(res, ls, rs);
		return res;
	}
}

int main(){
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++)
		scanf("%lld", &a[i]);
	for(int i = 1; i <= n; i++)
		scanf("%lld", &b[i]);
	build(1, 1, n);
	
	for(int i = 1; i <= m; i++){
		int op, x, y;
		scanf("%d%d%d", &op, &x, &y);
		if(op == 1)
			modify(1, x, y, 0);
		else if(op == 2)
			modify(1, x, y, 1);
		else{
			node res = query(1, x, y);
			printf("%lld\n", res.ans);
		}
	}
	return 0;
}
