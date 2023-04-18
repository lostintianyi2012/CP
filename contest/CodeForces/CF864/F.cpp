#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N = 4e5 + 5;

ll n, m, k, faMx[N], faMn[N], disMx[N], disMn[N], dfn[N], sz[N], tms;
ll A, B, C, ans;
vector<ll> eMx[N], eMn[N], reMx[N], reMn[N];
struct Dsu {
    ll fa[N];
    void init(ll x)
    {
        for (int i = 1; i <= x; i++)
            fa[i] = i;
    }
    ll find(ll x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }
    bool merge(ll x, ll y)
    {
        ll u = find(x), v = find(y);
        if (u == v)
            return 0;
        fa[u] = v;
        return 1;
    }
} dsu;
struct BIT {
    ll c[N], sz;
    void init(ll x)
    {
        sz = x;
        for (int i = 1; i <= x; i++)
            c[i] = 0;
    }
    ll lowbit(ll x) { return x & (-x); }
    void add(ll x, ll k)
    {
        for (; x <= sz; x += lowbit(x))
            c[x] += k;
    }
    ll ask(ll x)
    {
        ll k = 0;
        for (; x; x -= lowbit(x))
            k += c[x];
        return k;
    }
    ll Ask(ll x, ll y) { return ask(y) - ask(x - 1); }
} bit;
void dfs1(ll u)
{
    dfn[u] = ++tms;
    sz[u] = 1;
    disMx[u] = disMx[faMx[u]] + 1;
    B += disMx[u] - 1;
    for (ll v : reMx[u]) {
        dfs1(v);
        sz[u] += sz[v];
    }
}
void dfs2(ll u)
{
    disMn[u] = disMn[faMn[u]] + 1;
    A += disMn[u] - 1;
    C += bit.Ask(dfn[u], dfn[u] + sz[u] - 1);
    bit.add(dfn[u], 1);
    for (ll v : reMn[u])
        dfs2(v);
    bit.add(dfn[u], -1);
}

int main()
{
    scanf("%lld", &n);
    for (int i = 1; i < n; i++) {
        ll u, v;
        scanf("%lld%lld", &u, &v);
        if (u < v)
            swap(u, v);
        eMx[u].push_back(v);
        eMn[v].push_back(u);
    }
    dsu.init(n);
    for (int i = 1; i <= n; i++) {
        for (ll j : eMx[i]) {
            j = dsu.find(j);
            dsu.merge(j, i);
            faMx[j] = i;
            reMx[i].push_back(j);
        }
    }
    dsu.init(n);
    for (int i = n; i >= 1; i--) {
        for (ll j : eMn[i]) {
            j = dsu.find(j);
            dsu.merge(j, i);
            faMn[j] = i;
            reMn[i].push_back(j);
        }
    }
    bit.init(n);
    dfs1(n);
    dfs2(1);
    ans = A + B - 2 * C;
    printf("%lld\n", ans);
    for (scanf("%lld", &m); m; m--) {
        scanf("%lld", &k);
        disMn[++n] = disMn[k] + 1;
        ans += n - disMn[n];
        printf("%lld\n", ans);
    }
    return 0;
}