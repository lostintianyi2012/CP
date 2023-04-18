#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
typedef long long ll;

int main(){
	int T;
	scanf("%d", &T);

	while(T--){
		ll n, m, a, b;
		scanf("%lld%lld", &a, &b);
		scanf("%lld%lld", &n, &m);
		ll res = n % (m + 1);
		ll ans1 = (n / (m + 1) * a * m) + res * a;
		ll ans2 = (n / (m + 1) * a * m) + res * b;
		ll ans3 = n * b;
		printf("%lld\n", min(ans1, min(ans2, ans3)));
	}
	return 0;
}
