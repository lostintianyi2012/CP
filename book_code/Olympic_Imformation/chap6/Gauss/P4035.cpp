#include <iostream>
#include <algorithm>
#include <string.h>
#include <math.h>

const int N = 14;
const double eps = 1e-8;
double mat[N][N];
double x[N][N];
int n;

int Gauss_Jordan(){
	int line = 1;
	for(int i = 1; i <= n; i++){
		int maxn = line;
		for(int j = line + 1; j <= n; j++)
			if(fabs(mat[j][i]) > fabs(mat[maxn][i]))
				maxn = j;

		if(fabs(mat[maxn][i]) < eps)
			continue;

		for(int j = 1; j <= n + 1; j++)
			std::swap(mat[line][j], mat[maxn][j]);

		for(int j = 1; j <= n; j++){
			if(j == line)
				continue;
			double tmp = mat[j][i] / mat[line][i];
			for(int k = i; k <= n + 1; k++)
				mat[j][k] -= mat[line][k] * tmp;
		}
		line++;
	}
	return line > n;
}

int main(){
	scanf("%d", &n);
	for(int i = 0; i <= n; i++){
		for(int j = 1; j <= n; j++){
			scanf("%lf", &x[i][j]);
		}
	}
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= n; j++){
			mat[i][j] = 2 * (x[0][j] - x[i][j]);
		}
		for(int j = 1; j <= n; j++)
			mat[i][n + 1] += x[0][j] * x[0][j] - x[i][j] * x[i][j];
	}
	Gauss_Jordan();
	for(int i = 1; i <= n; i++)
		printf("%.3lf ", mat[i][n + 1] / mat[i][i]);
	return 0;
}
