#include <cstdio>
#include <cmath>
#include <iostream>
using namespace std;

const int N = 53;
double A[N][N];
const double eps = 1e-5;
int n;

int main(){
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= n+1; j++)
			scanf("%lf", &A[i][j]);
	int line = 1;

	for(int k = 1; k <= n; k++){
		int maxi = line;
		for(int i = line + 1; i <= n; i++)
			if(fabs(A[i][k]) > fabs(A[maxi][k])) 
				maxi =i;

		if(fabs(A[maxi][k]) < eps)
			continue;

		for(int j = 1; j <= n+1; j++)
			swap(A[line][j], A[maxi][j]);
		for(int i = 1; i <= n; i++){
			if(i == line)
				continue;
			double mul = A[i][k] / A[line][k];
			for(int j = k; j <= n+1; j++)
				A[i][j] -= A[line][j]*mul;
		}
		++line;
	}

	if(line <= n){
		while(line <= n)
			if(!(A[line++][n] < ) return puts("-1") && 0;
		return putchar('0') && 0;
	}
	for(int i =0; i < n; ++i){
		printf("x%d=", i+1);
		if(int(A[i][n]/A[i][i]*100) == 0) puts("0");
		else printf("%.2lf\n", A[i][n]/A[i][i]);
	}
}
