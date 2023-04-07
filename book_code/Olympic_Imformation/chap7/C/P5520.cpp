#include <iostream>
#include <algorithm>
#include <string.h>

using namespace std;
typedef long long ll;
ll n, m, p;
int type;

int main(){
	scanf("%d%lld%lld%lld", &type, &n, &m, &p);
	ll ans = 1;
	for(int i = n - m + 1; i >= n - 2 * m + 2; i--)
		ans = (ans * i) % p;
	printf("%lld\n", ans);
	return 0;
}
