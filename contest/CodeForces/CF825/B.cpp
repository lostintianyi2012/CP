#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <string.h>
#include <math.h>

using namespace std;
const int N = 1e5 + 10;
int a[N], b[N];
int n;

int gcd(int x, int y){
	return y == 0 ? x : gcd(y, x % y);
}

int main(){
	int T;
	scanf("%d", &T);
	while(T--){
		scanf("%d", &n);
		for(int i = 1; i <= n; i++)
			scanf("%d", &a[i]);
		if(n == 1){
			puts("YES");
			continue;
		}

		for(int i = 2; i <= n; i++)
			b[i] = a[i] * a[i-1] / gcd(a[i], a[i - 1]);
		b[1] = a[1], b[n + 1] = a[n];

		bool flag = true;
		for(int i = 1; i <= n; i++)
			if(a[i] != gcd(b[i], b[i+1])){
				flag = false;
				break;
			}

		if(flag)
			puts("YES");
		else
			puts("NO");
	}
	return 0;
}
