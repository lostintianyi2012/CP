#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;
const int N = 110;
int a[N];
int t;
int n;

inline void solve(){
	bool flag = true;
	if(a[0] == 1)
		flag = true;
	else
		flag = false;
	
	for(int i = 1; i < n; i++){
		if(a[i] == 1){
			if(flag)
				printf("-");
			else
				printf("+");
			flag = !flag;
		}
		else
			printf("+");
	}
	puts("");
}

int main(){
	scanf("%d", &t);
	while(t--){
		scanf("%d", &n);
		for(int i = 0; i < n; i++){
			scanf("%1d", &a[i]);
		}
		solve();
	}
	
	return 0;
}
