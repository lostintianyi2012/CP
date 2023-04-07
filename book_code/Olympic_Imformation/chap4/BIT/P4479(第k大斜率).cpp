/*
 * Author:lsty
 * Date:2023.1.28
 * Problem:P4479 第k大斜率
 * Tag:BIT
 */
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;
typedef long long ll;
typedef pair<int, int>  PII;
const int N = 1e5 + 10;
ll tr[N];
int n;
int px[N];

struct point{
    ll x, y, t;
    ll n_x;
}p[N];

int lowbit(int x){
    return x & -x;
}

bool cmp1(const point& a, const point& b){
    return a.t == b.t ? a.n_x < b.n_x : a.t < b.t;
}

void add(int x, int d){
    for(int i = x; i <= n; i += lowbit(i)){
        tr[i] += d;
    }
}

ll query(int x){
    ll ans = 0;
    for(int i = x; i > 0; i -= lowbit(i)){
        ans += tr[i];
    }
    return ans;
}

ll check(int _k){
    for(int i = 1; i <= n; i++){
        p[i].t = p[i].y - 1ll * _k * p[i].x;
    }
    sort(p + 1, p + 1 + n, cmp1);
    memset(tr, 0, sizeof tr);

    ll ans = 0;
    for(int i = 1; i <= n; i++){
        add(p[i].n_x, 1);
        ans += query(p[i].n_x - 1);
    }
    return ans;
}

int main() {
    ll k;
    scanf("%d%lld", &n, &k);
    for(int i = 1; i <= n; i++){
        scanf("%lld%lld", &p[i].x, &p[i].y);
        px[i] = p[i].x;
    }
    
    sort(px + 1, px + 1 + n);
    int tot = unique(px + 1, px + 1 + n) - px - 1;

    for(int i = 1; i <= n; i++){
        p[i].n_x = lower_bound(px + 1, px + tot + 1, p[i].x) - px;
    }

    int l = -2e8, r = 2e8;
    int ans = 0;
    while(l < r){
        int mid = (l + r) >> 1;
        if(check(mid) >= k)  {ans = mid, l = mid + 1;}
        else            r = mid;
    }
    printf("%d\n", ans);
    return 0;
}