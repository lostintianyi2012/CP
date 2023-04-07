#include <iostream>
#include <string.h>
#include <algorithm>

typedef long long ll;
int T;
int x[4];
ll ans = 0;

int same(int x, int y, int z){
	return ((x & 1) && (y & 1) && (z & 1));
}

int main(){
	scanf("%d", &T);
	while(T--){
		ans = 0;
		for(int i = 0; i < 3; i++)
			scanf("%d", &x[i]);
		std::sort(x, x + 3);
		if(!(same(x[0], x[1], x[2]) || same(x[0] ^ 1, x[1] ^ 1, x[2] ^ 1))){
			puts("-1");
			continue;
		}
		if(x[1] - x[0] <= x[2] - x[1]){
			//把 x[1] 变成 x[0]
			ans = (x[1] - x[0]) / 2;
			x[2] -= 2 * ans;
			x[0] = x[1];

			if((x[2] - x[1]) % 6){
				puts("-1");
				continue;
			}
			ans += (x[2] - x[1]) / 6 * 2;
		}
		else{
			ans = (x[2] - x[1]) / 2;
			x[0] += 2 * ans;
			x[2] = x[1];

			if((x[1] - x[0]) % 6){
				puts("-1");
				continue;
			}
			ans += (x[1] - x[0]) / 6 * 2;
		}
		printf("%lld\n", ans);
	}
	return 0;
}
