/*
 * Author:lsty
 * Date:2023.1.27
 * Problem:P1197 星球大战
 * Tag:DSU 倒序加边
 */
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;
typedef pair<int, int> PII;
const int N = 4e5 + 10;
int h[N], e[N], ne[N], from[N], idx;
int fa[N];
int star[N];
bool st[N];
int n, m;
int ans[N];
int k;
int dynamic_ans;

inline void add(int a, int b)
{
    from[idx] = a, e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}

int find(int x)
{
    if (x != fa[x]) {
        fa[x] = find(fa[x]);
    }
    return fa[x];
}

inline void merge(int x, int y)
{
    int fx = find(x), fy = find(y);
    if (fx == fy) {
        return;
    }

    if (fx != fy) {
        fa[fx] = fy;
        dynamic_ans--;
    }
}

int main()
{
    memset(h, -1, sizeof h);
    scanf("%d%d", &n, &m);

    for (int i = 0; i < n; i++) {
        fa[i] = i;
    }

    for (int i = 0; i < m; i++) {
        int x, y;
        scanf("%d%d", &x, &y);
        add(x, y), add(y, x);
    }

    scanf("%d", &k);
    for (int i = 0; i < k; i++) {
        scanf("%d", &star[i]);
        st[star[i]] = true;
    }

    dynamic_ans = n - k;

    for(int i = 0; i < 2 * m; i++){
        if(!st[from[i]] && !st[e[i]]){
            merge(from[i], e[i]);
        }
    }

    ans[k] = dynamic_ans;

    for (int d = k - 1; d >= 0; d--) {
        int u = star[d];
        st[u] = false;
        dynamic_ans++;

        for (int i = h[u]; ~i; i = ne[i]) {
            int v = e[i];
            if (!st[v]) {
                merge(u, v);
            }
        }
        ans[d] = dynamic_ans;
    }

    for (int i = 0; i <= k; i++) {
        printf("%d\n", ans[i]);
    }
    return 0;
}