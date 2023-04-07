---
tags: string, hash, bit, educational
---
对于一个 $01$ 字符串，如果将这个字符串 $0$ 和 $1$ 取反后，再将整个串反过来和原串一样，就称作“反对称”字符串。比如 $00001111$ 和 $010101$ 就是反对称的，$1001$ 就不是。
现在给出一个长度为 $n$ 的 $01$ 字符串，求它有多少个子串是反对称的。
$n \le 5 \times 10^5$

## Solution
对于字符串的反转相关操作，可以通过枚举对称轴来进行操作
枚举对称轴可以得到一些很好的性质：
许多性质在长度上具有单调性，比如回文，大区间回文则小区间一定回文（两端同时缩减）
对于这题，可以注意到所有反对称串长度一定为偶数，否则中点等于它自己的翻转，这不可能
枚举对称轴，可以发现这具有单调性，短的反对称串一定被长的反对称串包含
所以对原序列正着哈希一遍，对反转序列倒着哈希一遍，枚举对称轴，对每个对称轴二分得到极长的字符串即可
```cpp
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
```

## 另一种考虑方式
$a=b$ 的逻辑运算在 $\mathbb F_2$ 上可以看做是 $\neg a \oplus b$
如此，很多在二进制位上利用相等的方法可以扩展到不少 $\mathbb F_2$ 上的其他运算
例如这题，不妨把原来的限制看做是==异或意义下的回文串==
例如最简单的例子 $a_1a_2$ 是一个回文串，则满足 $[a_1=a_2]=1$
现在我们认为 $a_1\oplus a_2=1$ 才是一个回文串，这仍然能用求回文串的方法求，因为我们的方法 $a_1*a_2=1$ 这个逻辑表达式成立即可，不需要 $*$ 具有一些特殊的性质
所以，这题可以使用 Manacher求解回文串 $O(n)$ 完成计算