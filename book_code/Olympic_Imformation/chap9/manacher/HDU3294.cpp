#include <iostream>
#include <string.h>
#include <algorithm>
#include <stdio.h>

const int N = 2e5 + 10;
char s[N], str[N << 1], c;
int P[N << 1];
int pos[N << 1];
int n, len;
int d;

void build(){
	for(int i = 1; i <= n; i++){
		s[i] = ((s[i] - 'a' + d) + 26) % 26 + 'a';
	}
//	printf("%s\n", s + 1);

	len = 0;
	str[++len] = '$';
	str[++len] = '#';
	for(int i = 1; i <= n; i++)
		str[++len] = s[i], pos[len] = i, str[++len] = '#';
	str[++len] = '$';

	int c = 0, r = 0;
	for(int i = 2; i <= len; i++){
		if(i <= r)
			P[i] = std::min(P[(c << 1) - i], r - i + 1);
		else
			P[i] = 1;
		while(str[i + P[i]] == str[i - P[i]])
			P[i]++;
		if(i + P[i] > r)
			r = i + P[i] - 1, c = i;
	}
}

int main(){
	while(scanf("%c %s", &c, s + 1) != EOF){
//		printf("%c %s\n", c, s + 1);
		n = strlen(s + 1);
		d = 'a' - c;
		build();

		int maxp = 0;
		for(int i = 2; i <= len; i++)
			maxp = std::max(maxp, P[i]);
		if(maxp - 1 < 2){
			printf("No solution!\n");
			goto end;
		}

		for(int i = 2; i <= len; i++){
			if(P[i] == maxp){
				printf("%d %d\n", pos[i - P[i] + 2] - 1, pos[i + P[i] - 2] - 1);

				for(int j = i - P[i] + 1; j <= i + P[i] - 1; j++)
					if(str[j] != '#')
						printf("%c", str[j]);
				puts("");
				goto end;
			}
		}

		end:
		//读入换行符
		getchar();
	}
	return 0;
}
