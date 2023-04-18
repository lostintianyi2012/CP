#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>

using namespace std;
const int N = 2e5 + 10;
const int inf = 0x3f3f3f3f;
int a[N];
int b[N];

int main(){
	int T;
	scanf("%d", &T);
	while(T--){
		int n;
		int cnt[2] = {0, 0};
		scanf("%d", &n);
		for(int i = 1; i <= n; i++){
			scanf("%d", &a[i]);
			if(a[i] <= 1)
				cnt[a[i]]++;
		}
		if(cnt[0] == n)
			printf("%d\n", 1);
		else if(cnt[0] <= (n + 1) >> 1)
			printf("%d\n", 0);
		else if(cnt[0] + cnt[1] == n)
			printf("%d\n", 2);
		else
			printf("%d\n", 1);
	}

	return 0;
}
