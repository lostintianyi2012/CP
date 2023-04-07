#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
typedef long long ll;
const int N = 2e5 + 10;
ll dp[22][N];
ll a[N];
int n, k;
ll x;

int main(){
	int T;
	scanf("%d", &T);
	while(T--){
		scanf("%d%d%lld", &n, &k, &x);
		for(int i = 1; i <= n; i++){
			scanf("%lld", &a[i]);
			a[i] -= x;
		}
		ll ans = 0;
		for(int i = 1; i <= n; i ++){
			dp[0][i] = max(max(dp[0][i-1] + a[i], a[i]), 0ll);
			if(i <= n - k)
				ans = max(ans, dp[0][i]);
			for(int j = 1; j <= k; j ++){
				if(i < j)
					continue;
				if(i == j)
					dp[j][i] = max(dp[j-1][i-1] + a[i] + 2 * x, 0ll);
				else
					dp[j][i] = max(max(dp[j-1][i-1] + a[i] + 2 * x, dp[j][i-1] + a[i]), 0ll);
				if(i <= n - (k - j))
					ans = max(ans, dp[j][i]);
			}
		}

		printf("%lld\n", ans);
	}
	return 0;
}
