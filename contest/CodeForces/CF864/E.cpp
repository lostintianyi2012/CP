#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;
typedef long long ll;
const int N = 1e5 + 10, W = 5e6 + 10;
int prime[350000], phi[W], cnt;
bool not_prime[W];
int a[N];
int n, m;

void sieve()
{
	phi[1] = 1;
	for (int i = 2; i < W; i++) {
		if (!not_prime[i]) {
			phi[i] = i - 1;
			prime[++cnt] = i;
		}
		for (int j = 1; j <= cnt && i * prime[j] < W; j++) {
			not_prime[i * prime[j]] = true;
			if (i % prime[j]) {
				phi[i * prime[j]] = phi[i] * phi[prime[j]];
			} else {
				phi[i * prime[j]] = phi[i] * prime[j];
				break;
			}
		}
	}
}

int fa[7][W], dep[W];
void tree()
{
	dep[1] = 1;
	for (int i = 0; i < 7; i++)
		fa[i][1] = 1;
	for (int i = 2; i < W; i++) {
		dep[i] = dep[phi[i]] + 1;
		fa[0][i] = phi[i];
		for (int j = 1; j < 7; j++)
			fa[j][i] = fa[j - 1][fa[j - 1][i]];
	}
}

int LCA(int u, int v)
{
	if (dep[u] < dep[v])
		swap(u, v);
	for (int i = 6; i >= 0; i--)
		if (dep[fa[i][u]] >= dep[v])
			u = fa[i][u];
	if (u == v)
		return u;
	for (int i = 6; i >= 0; i--)
		if (fa[i][u] != fa[i][v])
			u = fa[i][u], v = fa[i][v];
	return fa[0][u];
}

struct node {
	int l, r;
	int lca, ignore;
	ll ans;
} tr[N << 2];

void pushup(int u){
	node &ls = tr[u << 1], &rs = tr[u << 1 | 1];
	tr[u].lca = LCA(ls.lca, rs.lca);
	tr[u].ans = ls.ans + rs.ans
				+ (ls.r - ls.l + 1) * (dep[ls.lca] - dep[tr[u].lca])
				+ (rs.r - rs.l + 1) * (dep[rs.lca] - dep[tr[u].lca]);
	tr[u].ignore = ls.ignore & rs.ignore;
}

void build(int u, int l, int r)
{
	tr[u].l = l, tr[u].r = r;
	if(l == r){
		tr[u].lca = a[l];
		tr[u].ignore = a[l] == 1;
		tr[u].ans = 0;
		return;
	}
	int mid = l + r >> 1;
	build(u << 1, l, mid);
	build(u << 1 | 1, mid + 1, r);
	pushup(u);
}

void modify(int u, int l, int r)
{
	if(tr[u].ignore)
		return; 
	if(tr[u].l == tr[u].r){
		tr[u].lca = phi[tr[u].lca];
		tr[u].ignore = (tr[u].lca == 1);
		return ;
	}
	int mid = tr[u].l + tr[u].r >> 1;
	if(l <= mid)
		modify(u << 1, l, r);
	if(r > mid)
		modify(u << 1 | 1, l, r);
	pushup(u);
}

int query_lca(int u, int l, int r)
{
	if(l <= tr[u].l && tr[u].r <= r) {
		return tr[u].lca;
	}
	int mid = tr[u].l + tr[u].r >> 1;
	if(r <= mid)
		return query_lca(u << 1, l, r);
	if(l > mid)
		return query_lca(u << 1 | 1, l, r);
	int lca = query_lca(u << 1, l, r);	
	return (LCA(lca, query_lca(u << 1 | 1, l, r)));
}

ll query_ans(int u, int l, int r, int lca)
{
	if(l <= tr[u].l && tr[u].r <= r) {
		return (ll)tr[u].ans + (ll)(tr[u].r - tr[u].l + 1) * (dep[tr[u].lca] - dep[lca]);
	}
	int mid = tr[u].l + tr[u].r >> 1;
	ll ans = 0;
	if(l <= mid)
		ans += query_ans(u << 1, l, r, lca);
	if(r > mid)
		ans += query_ans(u << 1 | 1, l, r, lca);
	return ans;
}

int main()
{
	sieve();
	tree();
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++)
		scanf("%d", &a[i]);
	build(1, 1, n);
	for(int i = 1; i <= m; i++){
		int op, l, r;
		scanf("%d%d%d", &op, &l, &r);
		if(op == 1)
			modify(1, l, r);
		else {
			int lca = query_lca(1, l, r);
			ll ans = query_ans(1, l, r, lca);
			printf("%lld\n", ans);
		}
	}	
	return 0;
}