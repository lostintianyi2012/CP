#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <set>

using namespace std;
typedef long long ll;
typedef pair<ll, int> pii;

const int N = 1e5 + 10;
int h[N], e[N << 1], ne[N << 1], idx;
ll w[N];
ll sum[N];
int siz[N], top[N], fa[N], son[N], cnt;
set<pii> sons[N];
int n, m;

inline void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}

void dfs(int u)
{
    siz[u] = 1;
	sum[u] = w[u];
    for (int i = h[u]; ~i; i = ne[i]) {
        int v = e[i];
        if (v == fa[u])
            continue;
        fa[v] = u;
        dfs(v);
        siz[u] += siz[v];
		sum[u] += sum[v];
		sons[u].insert({-siz[v], v});
        if (siz[v] > siz[son[u]] || (siz[v] == siz[son[u]] && v < son[u]))
            son[u] = v;
    }
}

int main()
{
    memset(h, -1, sizeof(h));
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    idx = 0, cnt = 0;
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        cin >> w[i];
    for (int i = 1; i < n; i++) {
        int a, b;
        cin >> a >> b;
        add(a, b), add(b, a);
    }

    dfs(1);
    while (m--) {
        int op, u;
        cin >> op >> u;
        if (op == 1) {
			cout << sum[u] << '\n';
        } else {
			int v = son[u];
			if(!v)
				continue;
			int p = fa[u];
			siz[u] -= siz[v];
			sum[u] -= sum[v];
			sons[u].erase({-siz[v], v});
			son[u] = sons[u].empty() ? 0 : (*sons[u].begin()).second;
			fa[u] = v;
			siz[v] += siz[u];
			sum[v] += sum[u];
			sons[v].insert({-siz[u], u});
			son[v] = (*sons[v].begin()).second;
			fa[v] = p;
			sons[p].erase({-siz[v], u});
			sons[p].insert({-siz[v], v});
			son[p] = (*sons[p].begin()).second;
        }
    }
    return 0;
}
