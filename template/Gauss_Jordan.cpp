#include <iostream>
#include <string.h>
#include <math.h>

const int N = 105;
double mat[N][N];
int n, m;

int main(){
	scanf("%d", &n);
	m = n + 1;

	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= m; j++){
			scanf("%lf", &mat[i][j]);
		}
	}
	for(int i = 1; i <= n; i++){
		int maxn = i;
		for(int j = i + 1; j <= n; j++){
			if(fabs(mat[j][i]) > fabs(mat[maxn][i]))
				maxn = j;
		}

		//交换最大
		for(int j = 1; j <= n + 1; j++){
			std::swap(mat[i][j], mat[maxn][j]);
		}
		if(!mat[i][i]){
			puts("No Solution");
			return 0;
		}

		for(int j = 1; j <= n; j++){
			if(j != i){
				double tmp = mat[j][i] / mat[i][i];
				for(int k = i + 1; k <= n + 1; k++)
					mat[j][k] -= mat[i][k] * tmp;
			}
		}
	}
	for(int i = 1; i <= n; i++)
		printf("%.2lf\n", mat[i][n + 1] / mat[i][i]);
	return 0;
}
