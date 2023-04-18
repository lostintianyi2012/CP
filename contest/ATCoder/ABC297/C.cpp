#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int N = 110;
char s[N][N];

int main(){
	int n, m;
	scanf("%d %d", &n, &m);
	for(int i = 1; i <= n; i++)
		scanf("%s", s[i] + 1);
	for(int i = 1; i <= n; i++)
		for(int j = 1; j < m; j++)
			if(s[i][j] == s[i][j + 1] && s[i][j] == 'T')
				s[i][j] = 'P', s[i][j + 1] = 'C';
	for(int i = 1; i <= n; i++)
		printf("%s\n", s[i] + 1);
	return 0;
}
