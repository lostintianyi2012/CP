#include <iostream>
#include <string.h>
#include <algorithm>

typedef long long ll;
const int N = 5e5 + 10;
const ll mod = 998244353;
const ll b = 131;
char s[N];
ll h1[N], h2[N];
ll power[N];
int n, mid;

ll f_pow(ll a, ll k){
    ll base = 1;
    for(; k; k >>= 1, a = (a * a) % mod){
        if(k & 1)
            base = (base * a) % mod;
    }
    return base;
}

ll clip(int l, int r, int type){
    if(type == 1){
        return ((h1[r] - h1[l-1] * power[r - l + 1] % mod) % mod + mod) % mod;
    }
    else{
        return ((h2[l] - h2[r+1] * power[r - l + 1] % mod) % mod + mod) % mod;
    }
}

bool check(int len){
    if(clip(mid - len + 1, mid, 1) == clip(mid + 1, mid + len, 2))
        return true;
    return false;
}

int main(){
    scanf("%d", &n);
    scanf("%s", s + 1);
    for(int i = 1; i <= n; i++)
        h1[i] = (h1[i-1] * b + s[i]) % mod;
    for(int i = n; i >= 1; i--)
        if(s[i] == '0')
            h2[i] = (h2[i+1] * b + '1') % mod;
        else
            h2[i] = (h2[i+1] * b + '0') % mod;
    power[0] = 1;
    for(int i = 1; i <= n; i++)
        power[i] = power[i - 1] * b % mod;

    ll ans = 0;
    for(mid = 1; mid < n; mid++){
        if(s[mid] == s[mid+1])
            continue;
        int l = 0, r = std::min(mid, n - mid);
        while(l < r){
            int mmid = (l + r + 1) >> 1;
            if(check(mmid))  l = mmid;
            else    r = mmid - 1;
        }
        ans += l;
    }
    printf("%lld\n", ans);
    return 0;
}