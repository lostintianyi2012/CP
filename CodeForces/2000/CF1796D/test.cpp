#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;
typedef long long ll;
const int N = 2e5 + 10;
ll dp[N];
ll premax[N];
ll a[N];
int n;

int main(){
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
		scanf("%lld", &a[i]);
	for(int i = 1; i <= n; i++){
		dp[i] = max(dp[i-1] + a[i], a[i]);
		premax[i] = max(premax[i-1], dp[i]);
	}
	printf("%lld\n", premax[n]);
	return 0;
}
