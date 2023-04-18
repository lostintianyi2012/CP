#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>

using namespace std;
const int N = 2e5 + 10;
int a[N];
int n;

int main(){
	int T;
	scanf("%d", &T);

	while(T--){
		scanf("%d", &n);
		for(int i = 1; i <= n; i++)
			scanf("%d", &a[i]);
		int l = 1, r = n;
		int mina = 1, maxa = n;
		while(l <= r){
			if(a[l] == mina)
				l++, mina++;
			if(a[r] == mina)
				r--, mina++;
			if(a[l] == maxa)
				l++, maxa--;
			if(a[r] == maxa)
				r--, maxa--;
			if((a[l] != mina && a[r] != maxa) && (a[l] != maxa && a[r] != mina))
					break;
		}
		if(l > r)
			puts("-1");
		else
			printf("%d %d\n", l, r);
	}
	return 0;
}
