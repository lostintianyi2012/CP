#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <set>

using namespace std;
typedef long long ll;
const int N = 5e5 + 10;
int a[N];
int col[N];

char gc(){
    static char buf[1 << 20], *p1, *p2;
    if(p1 == p2){
        p2 = (p1 = buf) + fread(buf, 1, 1 << 20, stdin);
    }
    return p1 == p2 ? EOF : *p1++;
}

inline ll read(){
    ll s = 0, w = 1;
    char c = gc();
    while(!isdigit(c)){
        if(c == '-')
            w = -1;
        c = gc();
    }
    while(isdigit(c)){
        s = (s << 3) + (s << 1) + (c ^ 48);
        c = gc();
    }
    return s * w;
}

int n;
int main(){
    n = read();
    for(int i = 1; i <= n; i++)
        a[i] = read();
    sort(a + 1, a + 1 + n);
    int idx = 0;
    for(int i = 1; i <= n; i++){
        if(a[i] != a[i-1])
            idx++;
        col[idx]++;
    }
    ll ans = 0;
    for(int i = 1; i <= idx; i++)
        ans += col[i] >> 1;
    printf("%lld\n", ans);
    return 0;
}