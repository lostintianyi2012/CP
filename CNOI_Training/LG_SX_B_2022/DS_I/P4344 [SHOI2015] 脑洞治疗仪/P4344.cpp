#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>

using namespace std;
typedef long long ll;
const int N = 2e5 + 10;
int n, m;

/*=========Fast Input==========*/
char gc(){
	static char buf[1 << 20], *p1, *p2;
	if(p1 == p2)
		p2 = (p1 = buf) + fread(buf, 1, 1 << 20, stdin);
	return p1 == p2 ? EOF : *p1++;
}

ll read(){
	ll s = 0;
	char c = gc();
	while(!isdigit(c))
		c = gc();
	while(isdigit(c)){
		s = (s << 3) + (s << 1) + (c ^ 48);
		c = gc();
	}
	return s;

}

/*========Segment Tree=========*/
struct node{
	int l, r;
	//前缀最长连续0, 后缀最长连续0, 区间最长连续0
	int pre, suf, len;
	//1的个数
	int sum;
	//-1代表没有标记, 0代表区间写0, 1代表区间写1
	int tag;
}tr[N << 2];

void pushup(int u){
	node &ls = tr[u << 1], &rs = tr[u << 1 | 1];
	if(rs.len == rs.r - rs.l + 1)
		tr[u].suf = ls.suf + rs.len;
	else
		tr[u].suf = rs.suf;
	if(ls.len == ls.r - ls.l + 1)
		tr[u].pre = ls.len + rs.pre;
	else
		tr[u].pre = ls.pre;

	tr[u].len = max(max(ls.len, rs.len), ls.suf + rs.pre);
	tr[u].sum = ls.sum + rs.sum;
}

void pushdown(int u){
	if(tr[u].tag == -1)
		return;
	node &ls = tr[u << 1], &rs = tr[u << 1 | 1];
	ls.pre = ls.suf = ls.len = (tr[u].tag^1) * (ls.r - ls.l + 1);
	rs.pre = rs.suf = rs.len = (tr[u].tag^1) * (rs.r - rs.l + 1);
	ls.sum = tr[u].tag * (ls.r - ls.l + 1);
	rs.sum = tr[u].tag * (rs.r - rs.l + 1);
	ls.tag = tr[u].tag;
	rs.tag = tr[u].tag;
	tr[u].tag = -1;
}

void build(int u, int l, int r){
	tr[u].l = l, tr[u].r = r;
	tr[u].tag = -1;
	tr[u].pre = tr[u].suf = 0;
	if(l == r){
		tr[u].len = 0;
		tr[u].sum = 1;
		return ;
	}
	int mid = l + r >> 1;
	build(u << 1, l, mid);
	build(u << 1 | 1, mid + 1, r);
	pushup(u);
}

void Cover(int u, int l, int r, int k){
	if(l <= tr[u].l && tr[u].r <= r){
		tr[u].tag = k;
		tr[u].len = tr[u].pre = tr[u].suf = (k^1) * (tr[u].r - tr[u].l + 1);
		tr[u].sum = k * (tr[u].r - tr[u].l + 1);
		return ;
	}
	pushdown(u);
	int mid = tr[u].l + tr[u].r >> 1;
	if(l <= mid)
		Cover(u << 1, l, r, k);
	if(r > mid)
		Cover(u << 1 | 1, l, r, k);
	pushup(u);
}

int Sum(int u, int l, int r){
	if(r < l)
		return 0;
	if(l <= tr[u].l && tr[u].r <= r){
		return tr[u].sum;
	}
	pushdown(u);
	int mid = tr[u].l + tr[u].r >> 1;
	int ans = 0;
	if(l <= mid)
		ans += Sum(u << 1, l, r);
	if(r > mid)
		ans += Sum(u << 1 | 1, l, r);
	return ans;
}

bool check(int l, int r, int k){
	int num = r - l + 1 - Sum(1, l, r);
	return num <= k;
}

int query(int u, int l, int r){
	if(l <= tr[u].l && tr[u].r <= r){
		return tr[u].len;
	}
	pushdown(u);
	int mid = tr[u].l + tr[u].r >> 1;
	if(l > mid)
		return query(u << 1 | 1, l, r);
	if(r <= mid)
		return query(u << 1, l,  r);
	return max(max(query(u << 1, l, r), query(u << 1 | 1, l, r)), min(tr[u << 1].suf, tr[u << 1 | 1].l - l) + min(tr[u << 1 | 1].pre, r - tr[u << 1].r));
}

int main(){
	freopen("input.in", "r", stdin);
	n = read(), m = read();
	build(1, 1, n);
	for(int i = 1; i <= m; i++){
		int op = read();
		if(op == 0){
			int l = read(), r = read();
			Cover(1, l, r, 0);
		}
		else if(op == 1){
			int l0 = read(), r0 = read();
			int l1 = read(), r1 = read();
			int k = Sum(1, l0, r0);
			if(k == 0)
				continue;
			Cover(1, l0, r0, 0);

			int l = l1, r = r1 + 1, ans = 0;
			while(l < r){
				int mid = l + r >> 1;
				if(check(l1, mid, k))	{ans = mid, l = mid + 1;}
				else r = mid;
			}
			Cover(1, l1, ans, 1);
//			for(int i = 1; i <= n; i++)
//				printf("%d ", Sum(1, i, i));
//			puts("");
		}
		else{
			int l = read(), r = read();
			int len = query(1, l, r);
			printf("%d\n", len);
		}
	}
	return 0;
}

