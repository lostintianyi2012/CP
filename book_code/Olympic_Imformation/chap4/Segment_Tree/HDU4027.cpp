/*
 * Author:lsty
 * Date:2023.2.4
 * Problem:HDU 4027 Can you answer these queries?
 * Tag:线段树
 */
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string.h>
#include <math.h>

const int N = 1e6 + 10;
int n, m;
long long a[N];

struct node{
    int l, r;
	long long sum;
    bool lazy_tag;
}tr[N << 2];

void pushup(int u){
	int ls = u << 1, rs = u << 1 | 1;
	tr[u].lazy_tag = tr[ls].lazy_tag & tr[rs].lazy_tag;
	if(tr[u].lazy_tag)
		tr[u].sum = tr[u].r - tr[u].l + 1;
	else
		tr[u].sum = tr[ls].sum + tr[rs].sum;
}

void build(int u, int l, int r){
	tr[u].l = l, tr[u].r = r;
	tr[u].sum = 0, tr[u].lazy_tag = 0;
	if(l == r){
		tr[u].sum = a[l];
		if(a[l] == 1)
			tr[u].lazy_tag = 1;
	}
	else{
		int mid = (l + r) >> 1;
		build(u << 1, l, mid);
		build(u << 1 | 1, mid + 1, r);
		pushup(u);
	}
}

void modify(int u, int l, int r){
	if(l <= tr[u].l && tr[u].r <= r){
		if(tr[u].lazy_tag)
			return ;
		else{
			//递归到叶子
			if(tr[u].l == tr[u].r){
				tr[u].sum = sqrt(tr[u].sum);
				tr[u].lazy_tag = (tr[u].sum == 1);
				return ;
			}

			int mid = (tr[u].l + tr[u].r) >> 1;
			modify(u << 1, l, r);
			modify(u << 1 | 1, l, r);
			pushup(u);
		}
	}
	else{
		int mid = (tr[u].l + tr[u].r) >> 1;
		if(l <= mid)	modify(u << 1, l, r);
		if(r > mid)		modify(u << 1 | 1, l, r);
		pushup(u);
	}
}

long long query(int u, int l, int r){
	if(l <= tr[u].l && tr[u].r <= r){
		return tr[u].sum;
	}
	int mid = (tr[u].l + tr[u].r) >> 1;
	long long ans = 0;
	if(l <= mid)	ans += query(u << 1, l, r);
	if(r > mid)		ans += query(u << 1 | 1, l, r);
	return ans;
}

int main(){
	int CASE = 0;
    while(scanf("%d", &n) != EOF){
		for(int i = 1; i <= n; i++){
			scanf("%lld", &a[i]);
		}

		build(1, 1, n);

		printf("Case #%d:\n", ++CASE);
		scanf("%d", &m);
		for(int i = 1; i <= m; i++){
			int op, l, r;
			scanf("%d%d%d", &op, &l, &r);
			if(l > r)
				std::swap(l, r);

			if(op == 0){
				modify(1, l, r);
			}
			else{
				printf("%lld\n", query(1, l, r));
			}
		}
		printf("\n");
	}
    return 0;
}