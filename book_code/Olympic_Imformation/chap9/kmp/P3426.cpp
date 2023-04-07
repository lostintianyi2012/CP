#include <iostream>
#include <string.h>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>

const int N = 5e5 + 10;
char s[N];
int Pi[N];
int n;
int f[N], bucket[N];

int main(){
	scanf("%s", s + 1);
	n = strlen(s + 1);
	for(int i = 2; i <= n; i++){
		int j = Pi[i-1];
		while(j && s[j + 1] != s[i])
			j = Pi[j];
		if(s[j + 1] == s[i])
			j++;
		Pi[i] = j;
	}
	f[1] = 1, bucket[1] = 1;
	for(int i = 2; i <= n; i++){
		f[i] = i;
		if(i - Pi[i] <= bucket[f[Pi[i]]])
			f[i] = f[Pi[i]];
		bucket[f[i]] = i;
	}
	printf("%d\n", f[n]);
	return 0;
}
