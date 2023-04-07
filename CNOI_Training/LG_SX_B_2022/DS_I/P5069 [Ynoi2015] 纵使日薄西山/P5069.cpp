#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <set>

using namespace std;
typedef long long ll;
const int N = 1e5 + 10;
const int inf = 0x3f3f3f3f;
ll a[N];
ll piece[N];
ll ans = 0;
int idx = 0;
int n, m;
set<int> pos;

/*==================FAST READIN=====================*/
char gc(){
	static char buf[100010], *p1, *p2;
	if(p1 == p2){
		p2 = (p1 = buf) + fread(buf, 1, 1 << 20, stdin);
	}
	return p1 == p2 ? EOF : *p1++;
}

inline ll read(){
	int s = 0, w = 1;
	char c = gc();
	while(!isdigit(c)){
		if(c == '-')	w = -1;
		c = gc();
	}
	while(isdigit(c))
		s = (s << 3) + (s << 1) + (c ^ 48), c = gc();
	return s * w;
}

/*=================Segment Tree=====================*/
struct node{
	int l, r;
	//仅左 / 仅右 / 都不 / 均选
	bool left[4], right[4];
	ll sum[4];
}tr[N << 2];

void pushup(int u){
	int mid = tr[u].l + tr[u].r >> 1;
	const node& ls = tr[u << 1], &rs = tr[u << 1 | 1];

	//都被选了
	if(ls.right[0] && rs.left[0]){
		//选前面的
		if(a[mid] >= a[mid + 1]){
			tr[u].left[0] = ls.left[0];
			tr[u].right[0] = rs.right[1];
			tr[u].sum[0] = ls.sum[0] + rs.sum[1];
		}
		else{
			//左侧只选左端点
			tr[u].left[0] = ls.left[2];
			tr[u].right[0] = rs.right[0];
			tr[u].sum[0] = ls.sum[2] + rs.sum[0];
		}
	}
	else{
		tr[u].left[0] = ls.left[0];
		tr[u].right[0] = rs.right[0];
		tr[u].sum[0] = ls.sum[0] + rs.sum[0];
	}

	if(ls.right[1] && rs.left[0]){
		if(a[mid] >= a[mid + 1]){
			tr[u].right[1] = rs.right[1];
			tr[u].sum[1] = ls.sum[1] + rs.sum[1];
		}
		else{
			tr[u].right[1] = rs.right[0];
			tr[u].sum[1] = ls.sum[3] + rs.sum[0];
		}
	}
	else{
		tr[u].right[1] = rs.right[0];
		tr[u].sum[1] = ls.sum[1] + rs.sum[0];
	}

	if(ls.right[0] && rs.left[2]){
		if(a[mid] >= a[mid + 1]){
			tr[u].left[2] = ls.left[0];
			tr[u].sum[2] = ls.sum[0] + rs.sum[3];
		}
		else{
			tr[u].left[2] = ls.left[2];
			tr[u].sum[2] = ls.sum[2] + rs.sum[2];
		}
	}
	else{
		tr[u].left[2] = ls.left[0];
		tr[u].sum[2] = ls.sum[0] + rs.sum[2];
	}

	if(ls.right[1] && rs.left[2]){
		if(a[mid] >= a[mid + 1])
			tr[u].sum[3] = ls.sum[1] + rs.sum[3];
		else
			tr[u].sum[3] = ls.sum[3] + rs.sum[2];
	}
	else
		tr[u].sum[3] = ls.sum[1] + rs.sum[2];
}

void build(int u, int l, int r){
	tr[u].l = l, tr[u].r = r;
	if(l == r){
		tr[u].sum[0] = a[l];
		tr[u].left[0] = tr[u].right[0] = true;
		return ;
	}
	int mid = l + r >> 1;
	build(u << 1, l, mid);
	build(u << 1 | 1, mid + 1, r);
	pushup(u);
}

void modify(int u, int x){
	if(tr[u].l == x && tr[u].r == x){
		tr[u].sum[0] = a[x];
		return ;
	}
	int mid = tr[u].l + tr[u].r >> 1;
	if(x <= mid)
		modify(u << 1, x);
	else
		modify(u << 1 | 1, x);
	pushup(u);
}

int main(){
	n = read();
	for(int i = 1; i <= n; i++)
		a[i] = read();
	
	build(1, 1, n);
	m = read();
	for(int i = 1; i <= m; i++){
		int x, k;
		x = read(), k = read();
		a[x] = k;
		modify(1, x);
		printf("%lld\n", tr[1].sum[0]);
	}
	return 0;
}
