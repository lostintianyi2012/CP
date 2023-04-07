#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdio>
#include <vector>

typedef long long ll;
typedef std::pair<ll, ll> pll;

ll x, y, l, r;
ll x_a = 0, y_b = 0;
std::vector<ll> unluck;
int main(){
	scanf("%lld%lld%lld%lld", &x, &y, &l, &r);

	for(ll i = 1; ; i *= x){
		for(ll j = 1;; j *= y){
			if(i + j >= l && i + j <= r)
				unluck.push_back(i + j);
			if(r / j < y)
				break;
		}
		if(r / i < x)
			break;
	}
	std::sort(unluck.begin(), unluck.end());

	if(unluck.size() == 0)
		printf("%lld\n", r - l + 1);
	else{
		ll ans = std::max(unluck[0] - l, r - unluck[unluck.size() - 1]);
		for(int i = 1; i < unluck.size(); i++)
			ans = std::max(ans, unluck[i] - unluck[i - 1] - 1);
		printf("%lld\n", ans);
	}
	return 0;
}
