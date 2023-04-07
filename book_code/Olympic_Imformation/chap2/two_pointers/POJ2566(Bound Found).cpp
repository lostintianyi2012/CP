/*
 * Author:lsty
 * Date:2023.1.27
 * Problem:POJ 2566 Bound Found
 * Tag:two pointers
 */
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;
typedef pair<long long, int> PII;
const int N = 100010;
int a[N];
PII s[N];
int n, m;
long long t;
long long ans = 0x3f3f3f3f, l, r;

inline void init()
{
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }
    s[0].first = 0;
    s[0].second = 0;

    for (int i = 1; i <= n; i++) {
        s[i].first = s[i - 1].first + a[i];
        s[i].second = i;
    }

    sort(s, s + 1 + n);
}

int main()
{
    while (scanf("%d%d", &n, &m) && (n || m)) {
        init();

        for (int i = 1; i <= m; i++) {
            scanf("%lld", &t);

            int l = 0, r = 1;
            int ans_l, ans_r;
            int min_dis = 0x3f3f3f3f;
            int ans;
            while(r <= n){
                long long d = s[r].first - s[l].first;

                if(abs(t - d) < min_dis){
                    min_dis = abs(t - d);
                    ans = d;
                    ans_l = s[l].second;
                    ans_r = s[r].second;
                }

                if(!min_dis)
                    break;
                if(d > t)
                    l++;
                else if(d < t)
                    r++;
                if(l == r)
                    r++;
            }
            if(ans_l > ans_r)
                swap(ans_l, ans_r);
            printf("%lld %d %d\n", ans, ans_l + 1, ans_r);
        }
    }
    return 0;
}