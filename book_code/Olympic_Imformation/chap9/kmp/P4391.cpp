#include <iostream>
#include <algorithm>

const int N = 1e6 + 10;
int Pi[N];
char s[N];
int n;

int main(){
	scanf("%d", &n);
	scanf("%s", s + 1);
	for(int i = 2; i <= n; i++){
		int j = Pi[i-1];
		while(j && s[i] != s[j + 1])
			j = Pi[j];
		if(s[i] == s[j + 1]) j++;
		Pi[i] = j;
	}
//	for(int i = 1; i <= n; i++)
//		printf("%d ", Pi[i]);
	printf("%d\n", n - Pi[n]);
	return 0;
}
