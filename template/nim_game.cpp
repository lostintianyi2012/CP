#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>

using namespace std;

int main(){
	int T;
	scanf("%d", &T);
	while(T--){
		int ans = 0;
		int n;
		scanf("%d", &n);
		for(int i = 1; i <= n; i++){
			int t;
			scanf("%d", &t);
			ans ^= t;
		}
		if(ans)
			puts("Yes");
		else
			puts("No");
	}
	return 0;
}
