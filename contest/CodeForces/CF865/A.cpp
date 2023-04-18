#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int N = 1e5 + 10;
int n;

int main(){
	int T;
	scanf("%d", &T);

	while(T--){
		int a, b;
		scanf("%d%d", &a, &b);
		int k = __gcd(a, b);
		if(k == 1){
			puts("1");
			printf("%d %d\n", a, b);
		}
		else{
			puts("2");
			printf("%d %d\n", a + 1, 1);
			printf("%d %d\n", a, b);
		}
	}
	return 0;
}
