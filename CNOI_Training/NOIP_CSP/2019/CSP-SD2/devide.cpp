#include <iostream>
#include <string.h>
#include <algorithm>
#include <queue>
typedef unsigned long long ull;

const int N = 4e7 + 10;
int n, type;
int a[N];

inline int read(){
    int s = 0, w = 1;
    char c = getchar();
    while(!isdigit(c)){
        if(c == '-')
            w = -1;
        c = getchar();
    }
    while(isdigit(c)){
        s = (s << 3) + (s << 1) + (c ^ 48);
        c = getchar();
    }
    return s * w;
}

namespace solution2{
    struct make{
        int p, l, r;
    }s[N];
    int x, y, z, m;
    ull b[N];
    const int mod = 1 << 30;
    void readin(){
        x = read(), y = read(), z = read();
        b[1] = read(), b[2] = read(), m = read();
        for(int i = 3; i <= n; i++)
            b[i] = ((ull)x * b[i-1] + (ull)y * b[i-2] + z) % mod;

        for(int i = 1; i <= m; i++)
            s[i].p = read(), s[i].l = read(), s[i].r = read();
        s[0].p = 0;
        for(int i = 1, j = 0; i <= n; i++){
            if(i > s[j].p)
                j++;
            a[i] = (b[i] % (s[j].r - s[j].l + 1)) + s[j].p;
        }
    }
}

void solve1(){
    ull last[5010];
    ull sum[5010];
    ull f[5010];
    sum[0] = 0;
    for(int i = 1; i <= n; i++){
        sum[i] = sum[i-1] + a[i];
    }

    memset(f, 0x7f, sizeof f);
    f[1] = a[1] * a[1];
    last[1] = a[1];
    for(int i = 2; i <= n; i++){
        for(int j = 1; j < i; j++){
            if(sum[i] - sum[j] >= last[j] && f[j] + (sum[i] - sum[j]) * (sum[i] - sum[j]) < f[i])
                f[i] = f[j] + (sum[i] - sum[j]) * (sum[i] - sum[j]), last[i] = sum[i] - sum[j];
        }
    }
    printf("%llu\n", f[n]);
}

int main(){
    scanf("%d%d", &n, &type);
    if(!type){
        for(int i = 1; i <= n; i++){
            scanf("%d", &a[i]);
        }
        solve1();
    }
    else
        solution2::readin();
    return 0;
}