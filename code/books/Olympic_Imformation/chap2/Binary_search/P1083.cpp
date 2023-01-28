#include <bits/stdc++.h>

using namespace std;
const int N = 1e6 + 10;
long long u[N], v[N], d[N], sum[N], w[N], a[N];
int n, m;

inline bool check(int x){
    memset(d, 0, sizeof d);
    for(int i = 1; i <= x; i++){
        d[u[i]] += w[i], d[v[i]+1] -= w[i];
    }

    for(int i = 1; i <= n; i++){
        sum[i] = sum[i-1] + d[i];
        if(sum[i] > a[i])
            return false;
    }

    return true;
}

int main(){
    scanf("%d%d", &n, &m);

    for(int i = 1; i <= n; i++){
        scanf("%lld", &a[i]);
    }

    for(int i = 1; i <= m; i++){
        scanf("%lld%lld%lld", &w[i], &u[i], &v[i]);
    }
    
    if(check(m)){
        puts("0");
        return 0;
    }
    else{
        int l = 0, r = m;
        while(l < r){
            int mid = (l + r) >> 1;
            if(check(mid))  l = mid+1;
            else    r = mid;
        }
        printf("-1\n%d\n", l);
    }
    return 0;
}