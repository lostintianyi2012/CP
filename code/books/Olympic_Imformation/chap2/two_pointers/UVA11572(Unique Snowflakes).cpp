/*
 * Author:lsty
 * Date:2023.1.27
 * Problem:UVA 11572 Unique Snowflakes
 * Tag:two pointers
 */
#include <algorithm>
#include <bits/extc++.h>
#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;
using namespace __gnu_cxx;
using namespace __gnu_pbds;

const int N = 1e6 + 10;
int a[N];

inline int read()
{
    int s = 0, w = 1;
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
    return s * w;
}

int main()
{
    int t;
    scanf("%d", &t);
    while (t--) {
        int ans = -1;
        int n;
        scanf("%d", &n);

        if(n == 0){
            printf("%d\n", 0);
            continue;
        }

        for (int i = 1; i <= n; i++) {
            scanf("%d", &a[i]);
        }

        cc_hash_table<int, int> hst;

        int l = 1, r = 1;
        hst[a[1]] = 1;
        while (r <= n) {
            ans = max(ans, r - l + 1);
            while (hst[a[r + 1]])
                hst[a[l++]] = 0;
            hst[a[r + 1]] = 1;
            r++;
        }
        printf("%d\n", ans);
    }
    return 0;
}