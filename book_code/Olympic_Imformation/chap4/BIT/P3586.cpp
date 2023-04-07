#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 1e6 + 10;
int n, m, cnt, a[N], x[N], y[N], val[N];
char c[N];
map<int, int> mp;
vector<int> v;
inline int lowbit(int x)
{
    return x & (-x);
}
struct FenwickTree {
    int tr[N];
    void init()
    {
        memset(tr, 0, sizeof(tr));
    }
    void add(int x, int val)
    {
        while (x <= cnt) {
            tr[x] += val;
            x += lowbit(x);
        }
    }
    int query(int x)
    {
        int ans = 0;
        while (x) {
            ans += tr[x];
            x -= lowbit(x);
        }
        return ans;
    }
} t1, t2;
void update(int x, int y)
{
    t1.add(a[x], -1);
    t1.add(y, 1);
    t2.add(a[x], -val[a[x]]);
    t2.add(y, val[y]);
    a[x] = y;
}
signed main()
{
    t1.init();
    t2.init();
    scanf("%lld%lld", &n, &m);
    v.push_back(0);
    for (int i = 1; i <= m; i++) {
        scanf("%s%lld%lld", &c[i], &x[i], &y[i]);
        v.push_back(y[i]);
    }

    sort(v.begin(), v.end());
    mp[v[0]] = ++cnt;
    val[1] = v[0];
    for (int i = 1; i < v.size(); i++) {
        if (v[i] != v[i - 1])
            cnt++;
        mp[v[i]] = cnt;
        val[cnt] = v[i];
    }

    for (int i = 1; i <= n; i++)
        a[i] = 1, t1.add(1, 1);
    for (int i = 1; i <= m; i++)
        y[i] = mp[y[i]];
    for (int i = 1; i <= m; i++) {
        if (c[i] == 'U')
            update(x[i], y[i]);
        else {
            int cnt = t1.query(y[i]), sum = t2.query(y[i]);
            if ((n - cnt) * val[y[i]] + sum >= x[i] * val[y[i]])
                printf("TAK\n");
            else
                printf("NIE\n");
        }
    }
    return 0;
}