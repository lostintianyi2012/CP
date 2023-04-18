#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;
typedef long long ll;
const int N = 1e6 + 10;

inline char gc() {
	static char buf[1 << 15], *p1 = buf, *p2 = buf;
	if(p1 == p2)
		p2 = (p1 = buf) + fread(buf, 1, 1 << 15, stdin);
	return p1 == p2 ? EOF : *p1++;
}

inline ll read() {
	ll s = 0, w = 1;
	char c = gc();
	while(!isdigit(c)){
		if(c == '-')	w = -1;
		c = gc();	
	}
	while(isdigit(c))
		s = (s << 3) + (s << 1) + (c ^ 48), c = gc();
	return s * w;
}

int n, m;
int rt[N << 1], a[N];
int cnt;
struct node {
	int ls, rs;
	int val;
}tr[N << 5];

void build(int &u, int l, int r) {
	u = ++cnt;
	if(l == r) {
		tr[u].val = a[l];
		return ;
	}
	int mid = l + r >> 1;
	build(tr[u].ls, l, mid);
	build(tr[u].rs, mid + 1, r);
}

int query(int u, int l, int r, int x) {
	if(l == r) {
		return tr[u].val;
	}
	int mid = l + r >> 1;
	if(x <= mid)
		return query(tr[u].ls, l, mid, x);
	else
		return query(tr[u].rs, mid + 1, r, x);	
}

void modify(int &u, int pre, int l, int r, int x, int val) {
	u = ++cnt;
	tr[u].ls = tr[pre].ls, tr[u].rs = tr[pre].rs, tr[u].val = tr[pre].val;
	if(l == r) {
		tr[u].val = val;
		return ;
	}
	int mid = l + r >> 1;
	if(x <= mid)
		modify(tr[u].ls, tr[pre].ls, l, mid, x, val);
	else
		modify(tr[u].rs, tr[pre].rs, mid + 1, r, x, val);
}

int main() {
	n = read(), m = read();
	for(int i = 1; i <= n; i++)
		a[i] = read();
	build(rt[0], 1, n);
	for(int i = 1; i <= m; i++) {
		int v, op;
		v = read(), op = read();
		if(op == 1) {
			int loc = read(), val = read();
			modify(rt[i], rt[v], 1, n, loc, val);
		}
		else {
			int loc = read();
			rt[i] = rt[v];
			printf("%d\n", query(rt[v], 1, n, loc));
		}
	}
	return 0;
}