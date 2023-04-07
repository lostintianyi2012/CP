#include <iostream>
#include <string.h>
#include <bitset>
#include <algorithm>

const int N = 1e3 + 10;
char row[N];
std::bitset<N> mat[N << 1];
int n, m;
int K;

void print_matrix(){
	for(int i = 1; i <= m; i++){
		for(int j = 1; j <= n + 1; j++){
			if(mat[i][j])
				printf("1 ");
			else
				printf("0 ");
		}
		puts("");
	}
	puts("");
}

int Gauss_Jordan(){
	int line = 1;
	//m 行 n 列
	for(int i = 1; i <= n; i++){
		int maxn = line;
		for(int j = line; j <= m; j++)
			if(mat[j][i]){
				maxn = j;
				break;
			}

		K = std::max(K, maxn);

		if(!mat[maxn][i])
			continue;

		std::swap(mat[maxn], mat[line]);
		for(int j = 1; j <= m; j++){
			if(j == line)
				continue;
			if(mat[j][i])
				mat[j] ^= mat[line];
		}
		line++;
//		print_matrix();
	}
	if(line <= n){
		return -1;
	}
	else
		return K;
}

int main(){
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= m; i++){
		scanf("%s", row + 1);

		for(int j = 1; j <= n; j++){
			mat[i][j] = row[j] - '0';
		}
		int t;
		scanf("%d", &t);
		mat[i][n + 1] = t;
	}
//	print_matrix();
	int ans = Gauss_Jordan();
	if(ans == -1)
		puts("Cannot Determine");
	else{
		printf("%d\n", K);
		for(int i = 1; i <= n; i++){
			if(mat[i][n + 1])
				puts("?y7M#");
			else
				puts("Earth");
		}
	}
	return 0;
}
