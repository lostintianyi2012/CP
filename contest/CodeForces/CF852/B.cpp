#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cstdlib>

using namespace std;
typedef long long ll;
const int N = 2e5 + 10;
ll a[N];
int n;

int main(){
	int T;
	scanf("%d", &T);
	while(T--){
		ll x, y;
		scanf("%lld%lld", &x, &y);
		n = 0;
		for(ll i = y; i <= x; i++)
			a[++n] = i;
		for(ll i = x - 1; i > y; i--)
			a[++n] = i;
		printf("%d\n", n);
		for(int i = 1; i <= n; i++)
			printf("%lld ", a[i]);
		puts("");
	}
	return 0;
}
