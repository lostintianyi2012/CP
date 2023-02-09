/*
 * Author:lsty
 * Date:2023.2.7
 * Problem:CF 868 F
 * Tag:决策单调性
 */
#include <iostream>
#include <cstdio>
#include <cstring>

const int N = 1e5 + 10;
long long f[N], g[N];
int a[N];
int n, k;

int cnt[N], nowl, nowr;
long long cost;

void Add(int x){
	cost += cnt[x];
	cnt[x]++;
}

void Del(int x){
	cnt[x]--;
	cost -= cnt[x];
}

void Move(int l, int r){
	while(nowr < r) Add(a[++nowr]);
	while(nowl > l) Add(a[--nowl]);
	while(nowr > r) Del(a[nowr--]);
	while(nowl < l) Del(a[nowl++]);
}

void solve(int l, int r, int ql, int qr){
	if(l > r)
		return ;
	int mid = l + r >> 1;
	int exepoint = -1;
	for(int i = qr; i >= ql; i--){
		if(i >= mid)
			continue;
		Move(i+1, mid);
		if(g[i] + cost < f[mid])
			f[mid] = g[i] + cost, exepoint = i;
	}
	solve(l, mid-1, ql, exepoint);
	solve(mid+1, r, exepoint, qr);
}

int main(){
	scanf("%d%d", &n, &k);
	for(int i = 1; i <= n; i++){
		scanf("%d", &a[i]);
	}

	memset(f, 0x3f, sizeof f);
	f[0] = 0;
	for(int i = 1; i <= k; i++){
		memcpy(g, f, sizeof g);
		memset(f, 0x3f, sizeof f);
		f[0] = 0;
		memset(cnt, 0, sizeof cnt);
		nowl = 1, nowr = 0;
		cost = 0;
		solve(1, n, 0, n);
	}
	printf("%lld\n", f[n]);
	return 0;
}