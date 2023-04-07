#include <iostream>
#include <algorithm>
#include <string.h>
#include <stdio.h>

using namespace std;
const int N = 110;
int a[N], b[N];
int main(){
	int T;
	scanf("%d", &T);	
	while(T--){
		int n;
		scanf("%d", &n);
		for(int i = 1; i <= n; i++)
			scanf("%d", &a[i]);
		for(int i = 1; i <= n; i++)
			scanf("%d", &b[i]);
		int cntdif, cnt0[] = {0, 0}, cnt1[] = {0, 0};
		cntdif = 0;
		for(int i = 1; i <= n; i++)
			if(a[i] != b[i])
				cntdif++;
		for(int i = 1; i <= n; i++){
			if(a[i] == 0)
				cnt0[0]++;
			else
				cnt1[0]++;
			if(b[i] == 0)
				cnt0[1]++;
			else
				cnt1[1]++;
		}
		printf("%d\n", min(cntdif, (int)abs(cnt0[0] - cnt0[1]) + 1));
	}
	return 0;
}
