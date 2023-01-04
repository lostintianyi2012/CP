#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;
int t;
int n, k;

int main(){
	scanf("%d", &t);
	while(t--){
		scanf("%d%d", &n, &k);
		if(k == 1){
			for(int i = 1; i <= n; i ++)
				printf("%d ", i);
			puts("");
		}
		else{
			for(int i = 1; i <= n; i ++){
				if(i % 2 == 0)
					printf("%d ", i/2);
				else
					printf("%d ", n - (i/2));
			}
			puts("");
		}
	}
	return 0;
}
