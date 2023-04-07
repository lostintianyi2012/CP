#include <iostream>
#include <algorithm>
#include <string.h>
#include <stdio.h>

using namespace std;
const int N = 1e3 + 10;

int main(){
	int T;
	scanf("%d", &T);
	while(T--){
		int n;
		scanf("%d", &n);
		//It can proof no solution only when n = 3
		if(n == 3){
			puts("NO");
			continue;
		}
		else
			puts("YES");
		int a[2];
		if(n & 1){
			//Construct (n/2 + 1)a + (n/2)b = a + b
			a[0] = n/2-1, a[1] = -(n/2);
		}
		else{
			a[0] = n, a[1] = -n;
		}
		for(int i = 1; i <= n; i++){
			printf("%d ", a[(i-1) & 1]);
		}
		puts("");
	}
	return 0;
}
