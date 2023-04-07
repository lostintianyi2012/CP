#include <iostream>
#include <stdio.h>
#include <string.h>
#include <algorithm>

const int N = 1e7 + 1e6 + 10;
char s[N];
char str[N << 1];
int len, P[N << 1];
int c, r, ans;

int main(){
	scanf("%s", s + 1);
	int n = strlen(s + 1);
	str[++len] = '$';
	str[++len] = '#';

	for(int i = 1; i <= n; i++)
		str[++len] = s[i], str[++len] = '#';

	for(int i = 2; i < len; i++){
		if(i <= r)
			P[i] = std::min(P[(c << 1) - i], r - i + 1);
		else
			P[i] = 1;
		while(str[i - P[i]] == str[i + P[i]])
			P[i]++;
		if(i + P[i] > r)
			r = i + P[i] - 1, c = i;
		ans = std::max(ans, P[i] - 1);
	}

	printf("%d\n", ans);
	return 0;
}
