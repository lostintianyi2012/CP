#include <iostream>
#include <algorithm>
#include <string.h>
#include <stdio.h>
#include <math.h>

typedef long long ll;
const int N = 50;
ll A[N] = {0, 1}, B[N] = {0, 1};
int n;

int LEN(int k){
	int ans = 0;
	while(k){
		ans++;
		k /= 10;
	}
	return ans;
}

int main(){
	for(int i = 2; i <= 35; i++){
		ll a = A[i-1], b = B[i-1];
		A[i] = a * (ll)i + b;
		B[i] = b * (ll)i;
		ll d = std::__gcd(A[i], B[i]);
		A[i] /= d, B[i] /= d;
	}

	while(scanf("%d", &n) != EOF){
		ll a = A[n] * n, b = B[n];
		ll d = std::__gcd(a, b);
		a /= d, b /= d;
		if(b == 1){
			printf("%lld\n", a);
			continue;
		}

		ll s = a / b;
		a -= s * b;

		int lb = log10(b) + 1, ls = log10(s) + 1;
		for(int i = 1; i <= ls + 1; i++)
			printf(" ");
		printf("%lld\n", a);

		printf("%lld ", s);
		for(int i = 1; i <= lb; i++)
			printf("-");
		printf("\n");
		for(int i = 1; i <= ls + 1; i++)
			printf(" ");
		printf("%lld\n", b);
	}
	return 0;
}
