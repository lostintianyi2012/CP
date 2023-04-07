#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <string.h>

const int N = 1e5 + 10;
char s[N], str[N << 1];
int P[N << 1];
int l[N << 1], R[N << 1];
int n, len;
int ans = 0;

void build(){
	str[++len] = '$';
	str[++len] = '#';
	for(int i = 1; i <= n; i++){
		str[++len] = s[i], str[++len] = '#';
	}
	str[++len] = '^';

	int c = 0, r = 0;
	for(int i = 2; i < len; i++){
		if(i <= r)	P[i] = std::min(P[(c << 1) - i], r - i + 1);
		else	P[i] = 1;

		while(str[i + P[i]] == str[i - P[i]])
			P[i]++;
		if(i + P[i] > r)
			r = i + P[i] - 1, c = i;

		l[i - P[i] + 1] = std::max(l[i - P[i] + 1], P[i] - 1);
		R[i + P[i] - 1] = std::max(R[i + P[i] - 1], P[i] - 1);
	}
}

int main(){
	scanf("%s", s + 1);
	n = strlen(s + 1);
	build();
	
	for(int i = 2; i <= len; i += 2)
		R[i] = std::max(R[i], R[i + 2] - 2);
	for(int i = len - 1; i >= 2; i -= 2)
		l[i] = std::max(l[i], l[i - 2] - 2);

	for(int i = 2; i <= len; i += 2)
		if(l[i] && R[i])
			ans = std::max(ans, l[i] + R[i]);

	printf("%d\n", ans);
	return 0;
}
