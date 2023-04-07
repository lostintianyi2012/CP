/*
 * Copyright© 2023 lsty. All rights reserved.
 * author: lsty
 * Problem: ZJOI2013 话旧
 * Tag: DP
 * Date: 2023-02-20 
 */
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>

using namespace std;
typedef long long ll;
const int maxk = 1e6 + 10;
const ll mod = 19940417;
ll f[maxk][2];
int n, k, maxt;

struct point{
    int x, y;
    bool operator < (point& a){
        return x < a.x;
    }
    bool operator == (point& a){
        return x == a.x;
    }
}p[maxk];

ll f_pow(ll x, ll a){
    ll base = 1;
    for(; a; a >>= 1, x *= x){
        x %= mod;
        if(a & 1){
            base *= x;
            base %= mod;
        }
    }
    return base;
}

int main() {
    scanf("%d%d", &n, &k);
    for(int i = 1; i <= k; i++){
        scanf("%d%d", &p[i].x, &p[i].y);
    }
    p[0].x = 0, p[k + 1].x = n;
    sort(p, p + k + 2);
    f[0][1] = 1;
    k = unique(p, p + k + 2) - p - 1;

    for(int i = 1; i <= k; i++){
        int x1 = p[i-1].x, y1 = p[i-1].y;
        int x2 = p[i].x, y2 = p[i].y;
        int len = x2 - x1 - y2 - y1;
        
        //上升
        if(x2 - x1 == y2 - y1){
            f[i][0] = (f[i][0] + f[i-1][0]) % mod;
            //前面是0, 可以把下降部分的答案也加上
            if(y1 == 0)
                f[i][0] = (f[i][0] + f[i-1][1]) % mod;
        }
        //下降
        else if(x2 - x1 == y1 - y2){
            //把上一个点上升和下降的答案都加上
            f[i][1] = (f[i][1] + (f[i-1][0] + f[i-1][1]) % mod) % mod;
        }
        //空中连接, 形成一个夹角(先上升再下降)
        else if(len < 0){
            f[i][1] = (f[i][1] + f[i-1][0]) % mod;
            if(y1 == 0)
                f[i][1] = (f[i][1] + f[i-1][1]) % mod;
        }
        //空中连接, 或者先碰地后上升
        else if(len == 0){
            f[i][1] = (f[i][1] + f[i-1][0]) % mod;
            if(y1 == 0)
                f[i][1] = (f[i][1] + f[i-1][1]) % mod;
            f[i][0] = (f[i][0] + (f[i-1][0] + f[i-1][1]) % mod) % mod;
        }
        else{
            //f[i-1][0]这种情况是len / 2, 而不是 len / 2 - 1
            ll t = (2 * f[i-1][0] + f[i-1][1]) % mod * f_pow(2, len / 2 - 1) % mod;
            if(y2 > 0)  f[i][0] = (f[i][0] + t) % mod;
            f[i][1] = (f[i][1] + t) % mod;
        }
        if(f[i][1] > 0)
            maxt = max(maxt, x2 - x1 + y1 + y2);
    }
    printf("%lld %d\n", f[k][1], maxt / 2);
    return 0;
}