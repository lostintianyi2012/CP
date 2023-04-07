#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>

using namespace std;
typedef long long ll;
const int N = 2e5 + 10;
int a[N];
int n, m;

struct node{
	int l, r;
	double cosa, sina;
	long long tag;
}tr[N << 2];

void pushup(int u){
	tr[u].cosa = tr[u << 1].cosa + tr[u << 1 | 1].cosa;
	tr[u].sina = tr[u << 1].sina + tr[u << 1 | 1].sina;
}

void mul(int u, double cosx, double sinx){
	double sina = tr[u].sina, cosa = tr[u].cosa;
	tr[u].sina = sina * cosx + cosa * sinx;
	tr[u].cosa = cosa * cosx - sina * sinx;
}

void pushdown(int u){
	if(!tr[u].tag)	return ;
	node &lson = tr[u << 1], &rson = tr[u << 1 | 1], &root = tr[u];
	double sinx = sin(root.tag), cosx = cos(root.tag);
	lson.tag += root.tag;
	rson.tag += root.tag;
	mul(u << 1, cosx, sinx);
	mul(u << 1 | 1, cosx, sinx);
	root.tag = 0;
}

void build(int u, int l, int r){
	tr[u].l = l, tr[u].r = r;
	if(l == r){
		tr[u].cosa = cos(a[l]);
		tr[u].sina = sin(a[l]);
		tr[u].tag = 0;
		return ;
	}
	int mid = l + r >> 1;
	build(u << 1, l, mid);
	build(u << 1 | 1, mid + 1, r);
	pushup(u);
}

void modify(int u, int l, int r, ll add, double cosx, double sinx){
	if(l <= tr[u].l && tr[u].r <= r){
		tr[u].tag += add;
		mul(u, cosx, sinx);
		return ;
	}
	pushdown(u);
	int mid = tr[u].l + tr[u].r >> 1;
	if(l <= mid)
		modify(u << 1, l, r, add, cosx, sinx);
	if(r > mid)
		modify(u << 1 | 1, l, r, add, cosx, sinx);
	pushup(u);
}

double query(int u, int l, int r){
	if(l <= tr[u].l && tr[u].r <= r){
		return tr[u].sina;
	}
	pushdown(u);
	double ans = 0;
	int mid = tr[u].l + tr[u].r >> 1;
	if(l <= mid)
		ans += query(u << 1, l, r);
	if(r > mid)
		ans += query(u << 1 | 1, l, r);
	return ans;
}

int main(){
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
		scanf("%d", &a[i]);
	build(1, 1, n);
	scanf("%d", &m);
	for(int i = 1; i <= m; i++){
		int op, l, r;
		scanf("%d%d%d", &op, &l, &r);
		if(op == 1){
			int v;
			scanf("%d", &v);
			modify(1, l, r, v, cos(v), sin(v));
		}
		else{
			printf("%.1lf\n", query(1, l, r));
		}
	}
	return 0;
}
