#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <string.h>

using namespace std;
typedef long long ll;
const int N = 2e5 + 10;
int a[N];
int n;
ll ans = 0;

int main(){
	int T;
	scanf("%d", &T);
	while(T--){
		ans = 0;
		scanf("%d", &n);
		for(int i = 1; i <= n; i++)
			scanf("%d", &a[i]);
		int l = 1, r = 0;
		while(l <= n){
			while(a[r] >= r - l + 1 && r <= n)
				r++;
			int len = (r - 1) - l + 1;
			ans += len;
			l++;
		}
		printf("%lld\n", ans);
	}
	return 0;
}
