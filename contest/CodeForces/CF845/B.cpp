#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;
const int N = 1e5 + 10, mod = 1e9 + 7;
long long fac[N];
int n;

int main(){
	fac[0] = 1;
	for(int i = 1; i <= 1e5 + 10; i++){
		fac[i] = (fac[i-1] * i) % mod;
	}

	int T;
	scanf("%d", &T);
	while(T--){
		scanf("%d", &n);
		printf("%lld\n", ((fac[n] * n % mod) * (n-1) % mod));
	}
	return 0;
}
