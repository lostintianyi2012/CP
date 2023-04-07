#include <iostream>
#include <algorithm>
#include <stdio.h>

typedef long long ll;
const int N = 1e6 + 10;
int n;
char str[N];
int Pi[N];
ll ans;

int main(){
	scanf("%d", &n);
	scanf("%s", str + 1);
	for(int i = 2; i <= n; i++){
		int j = Pi[i - 1];
		while(j && str[j + 1] != str[i])
			j = Pi[j];
		if(str[j + 1] == str[i])
			j++;
		Pi[i] = j;
	}
	
	for(int i = 2, j = 2; i <= n; i++, j = i){
		while(Pi[j])	j = Pi[j];
		if(Pi[i])
			Pi[i] = j;
		ans += i - j;
	}
	printf("%lld\n", ans);
	return 0;
}
