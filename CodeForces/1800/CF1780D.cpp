#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

void _minus(int x){
	printf("- %d\n", x);
	fflush(stdout);
}

void _output(int x){
	printf("! %d\n", x);
	fflush(stdout);
}

int main(){
	int T;
	scanf("%d", &T);
	while(T--){
		int ans = 0, cnt;
		scanf("%d", &cnt);
		while(cnt > 0){
			scanf("%d", &cnt);
			if(cnt == 0)
				break;
			int x = (1 << cnt) - 1;
			_minus(x);
			ans += x;
		}
		_output(ans);
	}
	return 0;
}
