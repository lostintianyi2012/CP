#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
typedef long long ll;

void query(int x, int y){
	printf("? %d %d\n", x, y);
	fflush(stdout);
}

void answer(ll x){
	printf("! %lld\n", x);
	fflush(stdout);
}

ll solve(){
	ll ans = 0;
	for(int k = 2; k <= 26; k++){
		ll x, y;
		query(1, k);
		scanf("%lld", &x);
		if(x == -1){
			return k - 1;
		}
		query(k, 1);
		scanf("%lld", &y);
		if(x != y){
			ans = x + y;
			return ans;
		}
	}
	return ans;
}

int main(){
	ll ans = solve();
	answer(ans);
	return 0;
}
