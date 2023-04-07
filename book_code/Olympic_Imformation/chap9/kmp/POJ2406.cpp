#include <iostream>
#include <string.h>
#include <algorithm>
#include <stdio.h>

const int N = 1e6 + 10;
char s[N];
int Pi[N];
int main(){
	while(scanf("%s", s + 1) != EOF){
		if(s[1] == '.'){
			break;
		}
		int n = strlen(s + 1);
		for(int i = 2; i <= n; i++){
			int j = Pi[i - 1];
			while(j && s[j + 1] != s[i])
				j = Pi[j];
			if(s[j + 1] == s[i])
				j++;
			Pi[i] = j;
		}
		if(n % (n - Pi[n]) == 0)
			printf("%d\n", n / (n - Pi[n]));
		else
			puts("1");
	}
	return 0;
}
