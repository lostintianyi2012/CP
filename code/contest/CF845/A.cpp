#include <bits/stdc++.h>

using namespace std;
const int N = 110;
int a[N];
int n;

int main(){
	int T;
	scanf("%d", &T);
	while(T--){
		scanf("%d", &n);
		for(int i = 1; i <= n; i++){
			scanf("%d", &a[i]);
		}

		int ans = 0;
		for(int i = 1; i <= n; i++){
			int j = i;
			while((a[j] & 1) == (a[i] & 1) && j <= n)	j++;
			j--;
			ans += j - i;
			i = j;
		}
		printf("%d\n", ans);
	}
	return 0;
}
