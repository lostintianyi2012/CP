#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <set>
#include <queue>
#define qingwa using
#define shi namespace
#define zhouxin std

qingwa shi zhouxin;
const int N = 1e6 + 10;
const int inf = 0x3f3f3f3f;
int a[N], maxai;
int L, R, n;
//k 的出现次数, k 在 [1, R] 的出现次数, k 在 (R, n] 的首次出现位置 
int times[N], Ltimes[N], Apos[N];
int i_times[N];
//Global pos[k]表示权值为 k 的在原序列中的下标 
int Gpos[N];
int ans;

/*=============Fast Input===============*/
inline char gc(){
	static char buf[1 << 20], *p1, *p2;
	if(p1 == p2){
		p2 = (p1 = buf) + fread(buf, 1, 1 << 20, stdin);
	}
	return p1 == p2 ? EOF : *p1++;
}

inline int read(){
	int s = 0;
	char c = gc();
	while(!isdigit(c)){
		c = gc();
	}
	while(isdigit(c)){
		s = (s << 3) + (s << 1) + (c ^ 48);
		c = gc();
	}
	return s;
}

/*===========Segment Tree============*/
//维护一个01序列 able[N]，其中第 i 个项为 1 表示 i 这个位置可以选
//否则表示不可以选 
struct node{
	int l, r;
	int sum;
}tr[N << 2];

void pushup(int u){
	tr[u].sum = tr[u << 1].sum + tr[u << 1 | 1].sum;
}

void build(int u, int l, int r){
	tr[u].l = l, tr[u].r = r;
	if(l == r){
		tr[u].sum = 0;
		return ;
	}
	int mid = l + r >> 1;
	build(u << 1, l, mid);
	build(u << 1 | 1, mid + 1, r);
	pushup(u);
}

void modify(int u, int x, int k){
	if(tr[u].l == x && tr[u].r == x){
		tr[u].sum = k;
		return; 
	}
	int mid = tr[u].l + tr[u].r >> 1;
	if(x <= mid)
		modify(u << 1, x, k);
	else
		modify(u << 1 | 1, x, k);
	pushup(u);
}

//返回下标在 (R, pos) 之间的首个 1 的位置
//不存在 1 返回 inf 
int query(int u, int l, int r){
	if(l <= tr[u].l && tr[u].r <= r){
		if(tr[u].l == tr[u].r)
			return tr[u].sum > 0 ? tr[u].l : inf;
		if(tr[u << 1].sum > 0)
			return query(u << 1, l, r);
		if(tr[u << 1 | 1].sum > 0)
			return query(u << 1 | 1, l, r);
		return inf;
	}
	if(tr[u].l == tr[u].r)
		return inf;
	int ans = inf;
	int mid = tr[u].l + tr[u].r >> 1;
	if(l <= mid)
		ans = min(ans, query(u << 1, l, r));
	if(r > mid)
		ans = min(ans, query(u << 1 | 1, l, r));
	return ans;
}

/*===============Major=================*/ 
void solve(){
	build(1, 1, n);
	for(int i = 1; i <= maxai; i++)
		//一开始某个元素就只出现了一次，直接加入 
		if(times[i] == 1)
			modify(1, Gpos[i], 1);
			
	//逐个移动 i 维护只出现过一次的 a[k] 的集合 
	for(int i = 1; i < L; i++){
		i_times[a[i]]--;
		//如果删完刚好剩一个就代表可以选了 
		if(i_times[a[i]] == 1)
			modify(1, Gpos[a[i]], 1);
		//如果已经被删干净了把对应位置变成 0 
		else if(i_times[a[i]] == 0)
			modify(1, Gpos[a[i]], 0);
		
		//在 [1, R] 之中出现了不止一次 
		if(Ltimes[a[i]] != 1)
			continue;
			
		//查询 (R, pos) 之中第一个 1 的位置 
		int rmin = query(1, R + 1, Apos[a[i]] - 1);
		if(rmin == inf)
			continue;
		ans = min(ans, rmin - i + 1);
	}
}

int main(){
	ans = inf;
	n = read(), L = read(), R = read();
	for(int i = 1; i <= R; i++){
		a[i] = read();
		times[a[i]]++;
		Ltimes[a[i]]++;
		Gpos[a[i]] = i;
		maxai = max(maxai, a[i]);
	} 
	for(int i = R + 1; i <= n; i++){
		a[i] = read();
		times[a[i]]++;
		if(!Apos[a[i]])
			Apos[a[i]] = i;
		Gpos[a[i]] = i;
		maxai = max(maxai, a[i]);
	}
	memcpy(i_times, times, sizeof times);
	//没出现过的就随便取
	for(int i = 1; i <= maxai; i++)
		if(!Apos[i])
			Apos[i] = n + 1;
	solve();
	if(ans == inf)
		printf("-1\n");
	else
		printf("%d\n", ans);
	return 0;
}
