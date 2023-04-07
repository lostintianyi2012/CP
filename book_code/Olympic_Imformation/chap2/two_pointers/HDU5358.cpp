#include <cstdio>
#include <iostream>
typedef long long ll;

using namespace std;
const int N = 1e5 + 10;
ll s[N], a[N];
ll pw[40];
int n;

inline ll get_sum(ll L, ll R)
{
    int l = 1, r = 1;
    ll res = 0;
    for (int i = 1; i <= n; i++) {
        l = max(i, l);
        r = max(i, r);
        while (l <= n && s[l] - s[i - 1] < L)
            l++;
        while (r <= n && s[r] - s[i - 1] < R)
            r++;

        r--;
        if (l > r)
            continue;
        if (s[r] - s[i - 1] >= R || s[r] - s[i - 1] < L)
            continue;
        if (s[l] - s[i - 1] >= R || s[l] - s[i - 1] < L)
            continue;
        res += (ll)(r - l + 1) * (ll)i + (ll)(r - l + 1) * (ll)(l + r) / 2;
    }
    return res;
}

int main()
{
    int t;
    scanf("%d", &t);

    for (int i = 0; i < 35; i++) {
        pw[i] = 1ll << i;
    }

    while (t--) {
        scanf("%d", &n);
        s[0] = 0;
        for (int i = 1; i <= n; i++) {
            scanf("%lld", &a[i]);
            s[i] = s[i - 1] + a[i];
        }

        ll ans = 0;
        for (int k = 1; k < 35; k++) {
            ans += (ll)k * get_sum(pw[k - 1], pw[k]);
        }
        ans += get_sum(0, 1);

        printf("%lld\n", ans);
    }

    return 0;
}