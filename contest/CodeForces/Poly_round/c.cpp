#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;
const int N = 2e5 + 20;
bool pure_0 = true, pure_1 = true;
int n;
//如果选择自己，实际上每一个0相当于从右侧选一个人踢出，每一个1相当于从左侧选一个人踢出
//如果不选自己，那么0和1都能从左边或右边踢走人
int main(){
	int t;
	scanf("%d", &t);
	while(t--){
		scanf("%d", &n);
		pure_0 = true, pure_1 = true;
		for(int i = 1; i < n; i++){
			int tmp;
			scanf("%1d", &tmp);
			if(tmp == 0)
				pure_1 = false;
			if(tmp == 1)
				pure_0 = false;
			if(pure_0 || pure_1)
				printf("1");
			else
				printf("%d", i);
			
			i == n-1 ? printf("\n") : printf(" ");
		}
	}
	return 0;
}
