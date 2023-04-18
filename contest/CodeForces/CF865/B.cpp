#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int N = 1e5 + 10;
int a[2][N];

int main(){
	int T;
	scanf("%d", &T);
	while(T--){
		int n;
		scanf("%d", &n);
		int idx = 2 * n - 2;
		for(int i = 2; i < n; i += 2){
			a[1][i-1] = idx--;
			a[0][i] = idx--;
		}
		for(int i = 1; i < n; i += 2){
			a[1][i-1] = idx--;
			a[0][i] = idx--;
		}
		a[0][0] = 2 * n - 1;
		a[1][n-1] = 2 * n;
		for(int k = 0; k < 2; k++){
			for(int i = 0; i < n; i++){
				printf("%d ", a[k][i]);
			}
			puts("");
		}
	}
	return 0;
}
