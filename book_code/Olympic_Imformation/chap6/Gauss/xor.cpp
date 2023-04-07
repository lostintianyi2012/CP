//This is the code for P3164
#include <iostream>
#include <algorithm>
#include <string.h>
#include <stdio.h>
#include <bitset>

using namespace std;
typedef long long ll;
const int N = 50;
const int dx[] = {0, 0, 1, 0, -1};
const int dy[] = {0, 1, 0, -1, 0};

int id[N][N];
bitset<N * N> mat[N * N];
int n, m;

int main(){
	scanf("%d %d", &n, &m);
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= m; j++)
			id[i][j] = (i-1) * m + j;

	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= m; j++)
			for(int k = 0; k < 5; k++){
				int x = i + dx[k], y = j + dy[k];
				if(x < 1 || y < 1 || x > n || y > m)
					continue;
				mat[id[i][j]][id[x][y]] = 1;
			}

	mat[1][1] = 0;
	mat[1][n * m + 1] = 1;

	for(int i = 1; i <= n * m; i++){
		int maxn = i;
		if(!mat[i][i])
			for(int j = i + 1; j <= n * m; j++)
				if(mat[j][i]){
					maxn = j;
					break;
				}

		if(i != maxn)
			std::swap(mat[i], mat[maxn]);

		for(int j = 1; j <= n * m; j++){
			if(j != i && mat[j][i] == 1)
				mat[j] ^= mat[i];
		}
	}

	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= m; j++){
			if(mat[id[i][j]][n * m + 1])
				putchar('1');
			else
				putchar('0');
			putchar(' ');
		}
		putchar('\n');
	}
	return 0;
}
