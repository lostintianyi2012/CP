#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cassert>

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
const int N = 1e5 + 10;
int h[N], e[N << 1], ne[N << 1], idx;
int dfn[N], rnk[N], top[N], siz[N], dep[N], son[N], fa[N], cnt;
int a[N];
int n;

void add(int u, int v) {
    e[idx] = v, ne[idx] = h[u], h[u] = idx++;
}

void dfs1(int u) {
    son[u] = -1, siz[u] = 1;

    for (int i = h[u]; ~i; i = ne[i]) {
        int v = e[i];

        if (v == fa[u])
            continue;

        fa[v] = u;
        dep[v] = dep[u] + 1;
        dfs1(v);
        siz[u] += siz[v];

        if (son[u] == -1 || siz[v] > siz[son[u]])
            son[u] = v;
    }
}

void dfs2(int u, int t) {
    top[u] = t;
    dfn[u] = ++cnt;
    rnk[cnt] = u;

    if (son[u] == -1) {
        return ;
    }

    dfs2(son[u], t);

    for (int i = h[u]; ~i; i = ne[i])
        if (e[i] != son[u] && e[i] != fa[u])
            dfs2(e[i], e[i]);
}

struct node {
    int l, r;
    ll sum;
    int tag;
} tr[N << 2];

void pushup(int u) {
    tr[u].sum = tr[u << 1].sum + tr[u << 1 | 1].sum;
}

void pushdown(int u) {
    if (tr[u].tag == -1)
        return ;

    node &ls = tr[u << 1], &rs = tr[u << 1 | 1];
    ls.tag = tr[u].tag;
    ls.sum = tr[u].tag * (ls.r - ls.l + 1);
    rs.tag = tr[u].tag;
    rs.sum = tr[u].tag * (rs.r - rs.l + 1);
    tr[u].tag = -1;
}

void build(int u, int l, int r) {
    tr[u].l = l, tr[u].r = r;
    tr[u].tag = -1;

    if (l == r) {
        tr[u].sum = a[l];
        return ;
    }

    int mid = l + r >> 1;
    build(u << 1, l, mid);
    build(u << 1 | 1, mid + 1, r);
    pushup(u);
}

void modify(int u, int l, int r, int k) {
    if (l <= tr[u].l && tr[u].r <= r) {
        tr[u].tag = k;
        tr[u].sum = k * (tr[u].r - tr[u].l + 1);
        return ;
    }

    pushdown(u);
    int mid = tr[u].l + tr[u].r >> 1;

    if (l <= mid)
        modify(u << 1, l, r, k);

    if (r > mid)
        modify(u << 1 | 1, l, r, k);

    pushup(u);
}

ll query(int u, int l, int r) {
    if (l <= tr[u].l && tr[u].r <= r) {
        return tr[u].sum;
    }

    ll ans = 0;
    pushdown(u);
    int mid = tr[u].l + tr[u].r >> 1;

    if (l <= mid)
        ans += query(u << 1, l, r);

    if (r > mid)
        ans += query(u << 1 | 1, l, r);

    return ans;
}

void modify_1_chain(int u) {
    while (~u) {
		assert(top[u] >= 0 && u >= 0);
        int l = dfn[top[u]], r = dfn[u];
		assert(l >= 1 && r >= 1);
        modify(1, l, r, 1);
        u = fa[top[u]];
    }
}

char op[15];
int main() {
    memset(h, -1, sizeof h);
    scanf("%d", &n);

    for (int i = 1; i < n; i++) {
        int u;
        scanf("%d", &u);
        add(u, i), add(i, u);
    }

    dfs1(0);
    dfs2(0, 0);
    fa[0] = -1;

    //  for(int u = 0; u < n; u++)
    //      printf("node #%d %d\n", u, dfn[u]);
    //      printf("node #%d seg:%d %d\n", u, seg[u].first, seg[u].second);
    //  puts("");

    build(1, 1, cnt + 2);

    int Q;
    scanf("%d", &Q);

    while (Q--) {
        scanf("%s", op);
        int x;
        scanf("%d", &x);

		int ans1 = tr[1].sum;
        if (op[0] == 'i') {
            modify_1_chain(x);
        } else {
			modify(1, dfn[x], dfn[x] + siz[x] - 1, 0);
        }
		int ans2 = tr[1].sum;
		ll ans = abs(ans1 - ans2);
        printf("%lld\n", ans);
    }

    return 0;
}

