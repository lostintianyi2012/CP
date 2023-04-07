#include <iostream>
#include <string.h>
#include <algorithm>
#include <stdio.h>
#include <stack>

const int N = 1e6 + 10;
char S[N], T[N];
int Pi[N];
int stk[N], tt;
int Match[N];

int main(){
	scanf("%s%s", S + 1, T + 1);
	int n = strlen(S + 1), m = strlen(T + 1);
	for(int i = 2; i <= m; i++){
		int j = Pi[i - 1];
		while(j && T[j + 1] != T[i])
			j = Pi[j];
		if(T[j + 1] == T[i])
			j++;
		Pi[i] = j;
	}
	
	int j = 0;
	for(int i = 1; i <= n; i++){
		while(j && T[j + 1] != S[i])
			j = Pi[j];
		if(S[i] == T[j + 1])
			j++;
		Match[i] = j;
		stk[++tt] = i;
		if(j == m){
			tt -= m;
			j = Match[stk[tt]];
		}
	}
	for(int i = 1; i <= tt; i++){
		printf("%c", S[stk[i]]);
	}
	return 0;
}
