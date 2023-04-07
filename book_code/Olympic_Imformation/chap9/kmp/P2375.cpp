#include <iostream>
#include <string.h>
#include <algorithm>
#include <stdio.h>

typedef long long ll;
const int N = 1e6 + 10;
const ll mod = 1e9 + 7;
int T;
char str[N];
int Pi[N];
ll t_num[N];
ll ans = 1;

int main(){
	scanf("%d", &T);
	while(T--){
		memset(t_num, 0, sizeof t_num);
		t_num[1] = 1;
		ans = 1;
		scanf("%s", str + 1);
		int n = strlen(str + 1);
		
		for(int i = 2; i <= n; i++){
			int j = Pi[i - 1];
			while(j && str[j + 1] != str[i])
				j = Pi[j];
			if(str[j + 1] == str[i])
				j++;
			Pi[i] = j;
			t_num[i] = t_num[j] + 1;
		}

		int j = 0;
		for(int i = 2; i <= n; i++){
			while(j && str[i] != str[j + 1])
				j = Pi[j];
			if(str[j + 1] == str[i])
				j++;
			while((j << 1) > i)	j = Pi[j];
			ans = (ans * (t_num[j] + 1)) % mod;
		}
		printf("%lld\n", ans);
	}
	return 0;
}
