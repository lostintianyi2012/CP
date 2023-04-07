#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdio>

using namespace std;
typedef long long ll;
const int N = 3.5e5 + 10;
const ll inf = 0x5f5f5f5f5f5f5f5f;
int n, k;
ll cold[N], hot[N];
ll a[N];
ll dp[N], ndp[N];

int main(){
	memset(dp, 0x5f, sizeof dp);
	int T;
	scanf("%d", &T);
	while(T--){
		memset(dp, 0x5f, (k + 2) * sizeof(ll));

		scanf("%d%d", &n, &k);
		for(int i = 1; i <= n; i++)
			scanf("%lld", &a[i]);
		for(int i = 1; i <= k; i++)
			scanf("%lld", &cold[i]);
		for(int i = 1; i <= k; i++)
			scanf("%lld", &hot[i]);

		dp[0] = 0;
		ll s = 0, minn = 0;
		for(int i = 1; i <= n; i++){
			int x = a[i], y = a[i-1];

			if(x == y){
				s += hot[x];
			}
			else{
				s += cold[x];
				dp[y] = min(dp[x] + hot[x], minn + cold[x]) - cold[x];
				minn = min(minn, dp[y]);
			}
		}
		printf("%lld\n", minn + s);
	}
	return 0;
}
