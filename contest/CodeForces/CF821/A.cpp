#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;
typedef long long ll;
const int N = 110, inf = 0x3f3f3f3f;
int t, n, k;
ll ans = 0;
int a[N];

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> t;
    while(t--){
        ans = 0;
        cin >> n >> k;
        for(int i = 1; i <= n; i++)
            cin >> a[i];
        for(int i = 1; i <= k; i++){
            int maxa = -inf;
            for(int j = i; j <= n; j += k)
                maxa = max(maxa, a[j]);
            ans += maxa;
        }
        printf("%lld\n", ans);
    }
    return 0;
}