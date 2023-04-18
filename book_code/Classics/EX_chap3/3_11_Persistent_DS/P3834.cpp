#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <assert.h>

using namespace std;
const int N = 2e5 + 10;
int n, m;
int len;
int cnt;

int a[N], b[N];
int rt[N];
struct node {
	int ls, rs;
	int sum;
}tr[N << 6];

inline int getid(const int &x)
{
	return lower_bound(b + 1, b + 1 + len, x) - b;
}

int build(int l, int r)
{
	int u = ++cnt;
	if(l == r)	return u;
	int mid = l + r >> 1;
	tr[u].ls = build(l, mid);
	tr[u].rs = build(mid + 1, r);
	return u;
}

int upd(int k, int l, int r, int last)
{
	int u = ++cnt;
	tr[u].ls = tr[last].ls, tr[u].rs = tr[last].rs, tr[u].sum = tr[last].sum + 1;
	if(l == r)	return u;
	int mid = l + r >> 1;
	if(k <= mid)
		tr[u].ls = upd(k, l, mid, tr[last].ls);
	else
		tr[u].rs = upd(k, mid + 1, r, tr[last].rs);
	return u;
}

int query(int u, int v, int l, int r, int k)
{
	int mid = l + r >> 1;
	int x = tr[tr[v].ls].sum - tr[tr[u].ls].sum;
	if(l == r)
		return l;
	if(k <= x)
		return query(tr[u].ls, tr[v].ls, l, mid, k);
	else
		return query(tr[u].rs, tr[v].rs, mid + 1, r, k - x);
}

int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++)
		scanf("%d", &a[i]);
	memcpy(b, a, sizeof(a));
	sort(b + 1, b + 1 + n);
	len = unique(b + 1, b + 1 + n) - b - 1;
	rt[0] = build(1, len);
	for(int i = 1; i <= n; i++)
		rt[i] = upd(getid(a[i]), 1, len, rt[i-1]);
	for(int i = 1; i <= m; i++)
	{
		int l, r, k;
		scanf("%d%d%d", &l, &r, &k);
		printf("%d\n", b[query(rt[l - 1], rt[r], 1, len, k)]);
	}
	return 0;
}