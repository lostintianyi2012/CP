#include <iostream>
#include <string.h>
#include <algorithm>

typedef long long ll;
const ll mod = 998244353;
const int N = 1e5 + 10;
int A[N];
int n;
int nw[N];
int mp[2049];
ll f[N];
ll ans = 0;
ll z = 1;
int cnt = 0;

int main(){
    freopen("cook.in", "r", stdin);
    freopen("cook.out", "w", stdout);
    memset(mp, -1, sizeof mp);
    mp[1] = 0, mp[2] = 1, mp[4] = 2, mp[8] = 3, mp[16] = 4, mp[32] = 5;
    mp[64] = 6, mp[128] = 7, mp[256] = 8, mp[512] = 9;
    mp[1024] = 10, mp[2048] = 11;

    std::cin >> n;
    for(int i = 1; i <= n; i++){
        scanf("%d", &A[i]);
        if(mp[A[i]] == -1){
            z = (z << 1) % mod;
            continue;
        }
        else
            nw[++cnt] = A[i];
    }

    f[0] = 1;
    for(int i = 1; i <= cnt; i++){
        for(int j = nw[i]; j >= 1; j--)
            f[2048] = (f[2048] + f[2048 + j - nw[i]]) % mod;
        for(int j = 2048; j >= nw[i]; j--)
            f[j] = (f[j] + f[j - nw[i]]) % mod;
    }
    printf("%lld\n", f[2048] * z % mod);
    return 0;
}