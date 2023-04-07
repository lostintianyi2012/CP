#include <iostream>
#include <string.h>
#include <algorithm>
#include <stdio.h>
#include <bitset>

const int N = 17;
const int dx[] = {0, 0, 1, 0, -1};
const int dy[] = {0, 1, 0, -1, 0};
std::bitset<N * N> mat[N * N];
int n, m;

int id(int x, int y){
	return (x-1) * n + y;
}

int Gauss_Jordan(){
	int line = 1;
	for(int i = 1; i <= n * n; i++){
		int maxn = line;
		for(int j = line; j <= n * n; j++)
			if(mat[j][i]){
				maxn = j;
				break;
			}
		if(!mat[maxn][i])
			continue;
		
		std::swap(mat[line], mat[maxn]);
		for(int j = 1; j <= n * n; j++){
			if(j == line)
				continue;
			if(mat[j][i])
				mat[j] ^= mat[line];
		}
		line++;
	}

	if(line <= n * n){
		while(line <= n * n)
			if(mat[line++][n * n + 1])
				return -1;
		goto count_ans;
	}

	count_ans:
	int ans = 0;
	for(int i = 1; i <= n * n; i++)
		if(mat[i][n * n + 1])
			ans++;
	return ans;
}

int main(){
	int T;
	scanf("%d", &T);
	while(T--){
		scanf("%d", &n);

		char s[N];
		for(int i = 1; i <= n; i++){
			scanf("%s", s + 1);

			for(int j = 1; j <= n; j++){
				for(int k = 0; k < 5; k++){
					int x = i + dx[k], y = j + dy[k];
					if(x < 1 || x > n || y < 1 || y > n)
						continue;
					mat[id(i, j)][id(x, y)] = 1;
				}

				if(s[j] == 'y')
					mat[id(i, j)][n * n + 1] = 0;
				else
					mat[id(i, j)][n * n + 1] = 1;
			}
		}

		int ans = Gauss_Jordan();
		if(ans == -1)
			printf("inf\n");
		else
			printf("%d\n", ans);
		for(int i = 1; i <= n * n; i++)
			mat[i].reset();
	}
	return 0;
}
