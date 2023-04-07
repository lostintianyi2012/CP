#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <bitset>

using namespace std;
typedef long long ll;
const int N = 1e5 + 10, M = 22;
int a[N];

struct node{
	int l, r;
	int len;
	//拆位
	int bit[M];
	bitset<M> xortag;
}tr[N << 2];

int n, m;

void pushup(int u){
	node& lson = tr[u << 1], rson = tr[u << 1 | 1];
	for(int i = 0; i < 21; i++){
		tr[u].bit[i] = lson.bit[i] + rson.bit[i];
		tr[u].len = lson.len + rson.len;
	}
}

void pushdown(int u){
	if(!tr[u].xortag.count())
		return ;
	node &lson = tr[u << 1], &rson = tr[u << 1 | 1];
	for(int i = 0; i < M; i++){
		if(tr[u].xortag[i]){
			lson.bit[i] = lson.len - lson.bit[i];
			rson.bit[i] = rson.len - rson.bit[i];
		}
	}
	lson.xortag ^= tr[u].xortag;
	rson.xortag ^= tr[u].xortag;
	tr[u].xortag.reset();
}

void build(int u, int l, int r){
	tr[u].l = l, tr[u].r = r;
	if(l == r){
		for(int i = 0; i < M; i++)
			if((a[l] >> i) & 1)
				tr[u].bit[i] = 1;
		tr[u].len = 1;
		return ;
	}
	int mid = l + r >> 1;
	build(u << 1, l, mid);
	build(u << 1 | 1, mid + 1, r);
	pushup(u);
}

ll query(int u, int l, int r){
	if(l <= tr[u].l && tr[u].r <= r){
		ll ans = 0;
		ll base = 1;
		for(int i = 0; i < M; i++){
			ans += base * tr[u].bit[i];
			base <<= 1;
		}
		return ans;
	}
	pushdown(u);

	ll ans = 0;
	int mid = tr[u].l + tr[u].r >> 1;
	if(l <= mid)
		ans += query(u << 1, l, r);
	if(r > mid)
		ans += query(u << 1 | 1, l, r);
	return ans;
}

void modify(int u, int l, int r, bitset<M> b){
	if(l <= tr[u].l && tr[u].r <= r){
		tr[u].xortag ^= b;
		for(int i = 0; i < M; i++)
			if(b[i])
				tr[u].bit[i] = (tr[u].len - tr[u].bit[i]);
		return ;
	}
	pushdown(u);

	int mid = tr[u].l + tr[u].r >> 1;
	if(l <= mid)
		modify(u << 1, l, r, b);
	if(r > mid)
		modify(u << 1 | 1, l, r, b);
	pushup(u);
}

void change(int l, int r, ll x){
	bitset<M> b;
	for(int i = 0; i < 21; i++)
		if((x >> i) & 1)
			b[i] = 1;
	modify(1, l, r, b);
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> n;
	for(int i = 1; i <= n; i++)
		cin >> a[i];
	build(1, 1, n);
	cin >> m;

	for(int i = 1; i <= m; i++){
		int op, l, r;
		cin >> op >> l >> r;
		if(op == 1){
			ll ans = query(1, l, r);
			cout << ans << '\n';
		}
		else{
			ll x;
			cin >> x;
			change(l, r, x);
		}
	}
	return 0;
}
