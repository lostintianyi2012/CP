#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <cstring>

using namespace std;

const int N = 1e3 + 10;
int Pi[N];
char s1[N], s2[N];
int main(){
	while(scanf("%s %s", s1 + 1, s2 + 1) != EOF){
		if(s1[1] == '#')
			break;
		int n = strlen(s2 + 1);

		for(int i = 2; i <= n; i++){
			int j = Pi[i - 1];
			while(j && s2[j + 1] != s2[i])
				j = Pi[j];
			if(s2[j + 1] == s2[i]) j++;
			Pi[i] = j;
		}
		
		int ans = 0;
		int m = strlen(s1 + 1);
		int cur = 0;
		for(int i = 1; i <= m; i++){
			while(cur && s2[cur + 1] != s1[i])
				cur = Pi[cur];
			if(s2[cur + 1] == s1[i]) cur++;
			if(cur == n){
				cur = 0;
				ans++;
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}
