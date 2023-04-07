/*
 * Author:lostintianyi
 * Date:2023.1.13
 * Problem:P5465 星际穿越
 */
#include <bits/stdc++.h>

using namespace std;
const int N = 3e5 + 10;
int L[N];
int go[21][N];
int f[21][N];
int g[21][N];
int n;
int q;

inline long long get(long long x, long long r){
    if(L[x] <= r)
        return x - r;
    
    long long ans = x - L[x], tot = 1;
    x = L[x];
    //tot表示已经跳的步数
    for(int i = 20; i >= 0; i--){
        if(f[i][x] >= r){
            //这些点到起始点仍需要tot步 + 跳的步数之和
            ans += tot * (x - f[i][x]) + g[i][x];
            tot += (1 << i);
            x = f[i][x];
        }
    }

    if(x > r)
        ans += tot * (x - r) + x - r;
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
        //f[0][i] 表示 i到n所有的最小值
        //用来计算后面的答案
        f[0][i] = min(f[0][i+1], L[i]);
        g[0][i] = i - f[0][i];
    }

    for(int j = 1; j <= 20; j++){
        for(int i = (1 << j); i <= n; i++){
            f[j][i] = f[j-1][f[j-1][i]];
            g[j][i] = g[j-1][i] + g[j-1][f[j-1][i]] + (1 << (j-1)) * (f[j-1][i] - f[j][i]);
        }
    }

    scanf("%d", &q);
    while(q--){
        int l, r, x;
        scanf("%d%d%d", &l, &r, &x);
        long long ans = get(x, l) - get(x, r+1);
        long long fra = r - l + 1;
        int d = __gcd(ans, fra);
        ans /= d, fra /= d;
        printf("%lld/%lld\n", ans, fra);
    }

    return 0;
}