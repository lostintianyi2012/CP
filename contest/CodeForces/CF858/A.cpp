#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>

using namespace std;

int main(){
	int T;
	scanf("%d", &T);

	while(T--){
		int a, b, c, d;
		scanf("%d%d%d%d", &a, &b, &c, &d);
		if(b > d){
			puts("-1");
			continue;
		}
		int len = d - b;
		if(a + len < c){
			puts("-1");
			continue;
		}
		int ans = len + (a + len) - c;
		printf("%d\n", ans);
	}
	return 0;
}
