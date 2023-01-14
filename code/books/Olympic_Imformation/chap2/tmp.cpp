#include <bits/stdc++.h>

using namespace std;
const int N = 3e5 + 10;
int f[22][N]; 
long long g[22][N];
int L[N];
int n;

long long get(int x, int to){
    if(L[x] <= to)
        return x - to;
    long long ans = x - L[x];
    //总计跳的步数
    int tot = 1;
    x = L[x];
    for(int i = 20; i >= 0; i--){
        if(f[i][x] >= to){
            ans += tot * (x - f[i][x]) + g[i][x];
            tot += (1 << i);
            x = f[i][x];
        }
    }
    if(x > to)
        ans += tot * (x - to) + x - to;
    return ans;
}
int main(){
    scanf("%d", &n);
    for(int i = 2; i <= n; i++){
        scanf("%d", &L[i]);
    }
    f[0][n] = L[n];
    g[0][n] = n - L[n];

    for(int i = n-1; i >= 2; i--){
        f[0][i] = min(f[0][i+1], L[i]);
        g[0][i] = i - f[0][i];
    }

    for(int i = 1; i <= 20; i++){
        for(int j = (1 << i); j <= n; j++){
            f[i][j] = f[i-1][f[i-1][j]];
            g[i][j] = g[i-1][j] + g[i-1][f[i-1][j]] + (1 << (i-1)) * (f[i-1][j] - f[i][j]);
        }
    }
    
    int q;
    scanf("%d", &q);
    while(q--){
        int l, r, x;
        scanf("%d%d%d", &l, &r, &x);
        long long ans = get(x, l) - get(x, r+1);
        long long fac = r - l + 1;
        int d = __gcd(ans, fac);
        printf("%lld/%lld\n", ans/d, fac/d);
    }

    return 0;
}