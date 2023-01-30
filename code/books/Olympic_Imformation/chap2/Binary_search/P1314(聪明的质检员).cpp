/*
 * Author:lsty
 * Date:2023.1.27
 * Problem:P1314 聪明的质检员
 * Tag:
 */
#include <algorithm>
#include <cstdio>
#include <iostream>

using namespace std;
const int N = 2e5 + 10;
int n, m;
long long s;
int w[N], v[N];
int seg_l[N], seg_r[N];
long long st[N];
long long pre_v[N];
int times[N];

inline long long read()
{
    long long s = 0;
    int w = 1;
    char c = getchar();
    while (!isdigit(c)) {
        if (c == '-')
            w = -1;
        c = getchar();
    }
    while (isdigit(c)) {
        s = (s << 3) + (s << 1) + (c ^ 48);
        c = getchar();
    }
    return w * s;
}

inline long long calc_ans(int x)
{
    for (int i = 1; i <= n; i++) {
        if (w[i] >= x)
            st[i] = st[i-1] + 1, pre_v[i] = pre_v[i-1] + v[i];
        else
            st[i] = st[i-1], pre_v[i] = pre_v[i-1];
    }

    long long y = 0;
    for (int i = 1; i <= m; i++) {
        y += (pre_v[seg_r[i]] - pre_v[seg_l[i] - 1]) * (st[seg_r[i]] - st[seg_l[i] - 1]);
    }
    return y;
}

int main()
{
    n = read(), m = read(), s = read();
    int maxw = -1;
    for (int i = 1; i <= n; i++) {
        w[i] = read(), v[i] = read();
        maxw = max(maxw, w[i]);
    }

    for (int i = 1; i <= m; i++) {
        seg_l[i] = read();
        seg_r[i] = read();
    }

    int l = 0, r = maxw + 2;
    long long ans = 0x3f3f3f3f3f3f3f3f;
    while (l < r) {
        int mid = (l + r) >> 1;

        long long y = calc_ans(mid);
        
        if (y > s)
            l = mid + 1;
        else
            r = mid;
        ans = min(ans, llabs(s - y));
    }

    printf("%lld\n", ans);
    return 0;
}