#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;
typedef long long ll;
const int N = 2e5 + 10;
const ll inf = 0x3f3f3f3f3f3f3f3f;
ll p[N];
int n;

int main(){
	int T;
	scanf("%d", &T);

	while(T--){
		scanf("%d", &n);
		for(int i = 1; i <= n << 1; i++)
			scanf("%lld", &p[i]);

		ll ans = inf;
		if(n == 1){
			ans = min(ans, 1ll * abs(p[1] - p[2]));
		}
		if(n == 2){
			ll s = 0;
			for(int i = 1; i <= n << 1; i++)
				s += abs(p[i] - 2);
			ans = min(ans, s);
		}
		if(n % 2 == 0){
			ll s = 0;
			for(int i = 1; i <= n << 1; i++)
				s += abs(p[i] + 1);
			for(int i = 1; i <= n << 1; i++){
				ll t = s - abs(p[i] + 1) + abs(p[i] - n);
				ans = min(ans, t);
			}
		}
		ll s = 0;
		for(int i = 1; i <= n << 1; i++)
			s += abs(p[i]);
		ans = min(ans, s);
		printf("%lld\n", ans);
	}
	return 0;
}
