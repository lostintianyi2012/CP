#include <iostream>
#include <stdio.h>
#include <algorithm>

const int N = 3e5 + 10;
long long a[N], b[N], t[N], t2[N];
int n, m;
long long ans = 0;
int main(){
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; i++){
        scanf("%lld", &a[i]);
    }
    for(int i = 1; i <= m; i++){
        scanf("%lld", &b[i]);
        t[i] = b[i];
    }
    std::sort(t + 1, t + 1 + m);
    std::sort(a + 1, a + 1 + n);
    for(int i = 1; i <= m; i++){
        t2[i] = t2[i-1] + t[i];
    }
    ans = a[1] * (m-1) + t[1] * (n-1);
    for(int i = 2; i <= n; i++){
        //第一个 \ge a[i] 的 bi
        int k = std::lower_bound(t + 2, t + 1 + m, a[i]) - t;
        ans += t2[k-1] - t2[1] + (m - k + 1) * a[i];
    }
    printf("%lld\n", ans);
    return 0;
}