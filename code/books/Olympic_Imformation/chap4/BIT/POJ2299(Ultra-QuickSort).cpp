/*
 * Author:lsty
 * Date:2023.1.28
 * Problem:POJ2299
 * Tag:BIT
 */
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;
const int N = 500010;
int tr[N], rnk[N];
int n;

struct node{
    int val, id;
    bool operator < (const node& w) const {
        return val == w.val ? id < w.id : val < w.val;
    }
}a[N];

inline int lowbit(int x)
{
    return x & -x;
}

inline void add(int x, int k)
{
    for (int i = x; i <= n; i += lowbit(i))
        tr[i] += k;
}

inline long long query(int x)
{
    long long ans = 0;
    for (int i = x; i > 0; i -= lowbit(i))
        ans += tr[i];
    return ans;
}

int main()
{
    while (scanf("%d", &n) != EOF && n) {
        memset(tr, 0, sizeof tr);

        for (int i = 1; i <= n; i++) {
            scanf("%d", &a[i].val);
            a[i].id = i;
        }

        sort(a + 1, a + 1 + n);

        for (int i = 1; i <= n; i++)
            rnk[a[i].id] = i;

        long long ans = 0;
        for (int i = n; i > 0; i--) {
            add(rnk[i], 1);
            ans += query(rnk[i] - 1);
        }
        printf("%lld\n", ans);
    }
    return 0;
}