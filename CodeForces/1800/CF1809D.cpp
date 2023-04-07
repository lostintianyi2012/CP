#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string>
#include <cstring>

using namespace std;
typedef long long ll;
const int N = 3e5 + 10;
const ll cost1 = 1e12, cost2 = 1e12 + 1;
int pre[N];
char s[N];

int main(){
	int T;
	cin >> T;
	while(T--){
		scanf("%s", s + 1);
		int n = strlen(s + 1);
		ll ans = 1e18;
		for(int i = 1; i <= n; i++)
			pre[i] = pre[i-1] + !(s[i] - '0');
		
		for(int i = 0; i <= n; i++){
			ll one = i - pre[i];
			ll zero = pre[n] - pre[i];
			if(i != 0 && s[i] == '0' && s[i-1] == '1'){
				ans = min(ans, (zero + one) * cost2 - 1);
			}
			else{
				ans = min(ans, (zero + one) * cost2);
			}
		}
		if(n == 1)
			ans = 0;
		printf("%lld\n", ans);
	}
	return 0;
}
