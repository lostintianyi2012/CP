#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <string.h>

using namespace std;
typedef long long ll;
const int N = 2e5 + 10;
int a[N];
int Right[N];
int f[N], g[N];
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
			Right[l] = r - 1;
			int len = Right[l] - l + 1;
			ans += len;
			l++;
		}
	}
	return 0;
}

