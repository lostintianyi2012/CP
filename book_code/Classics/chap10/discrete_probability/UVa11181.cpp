#include <iostream>
#include <algorithm>
#include <string.h>
#include <math.h>

const int N = 25;
double p[N];
double P_E;
double P_E_i;
int n, r;

void dfs1(int k, int d, double now){
	if(d > r)
		return ;
	if(k == n + 1){
		if(d == r)
			P_E += now;
		return;
	}
	dfs1(k + 1, d, now * (1 - p[k]));
	dfs1(k + 1, d + 1, now * p[k]);
	return ;
}

void dfs2(int k, int i, int d, double now){
	if(d > r)
		return ;
	if(k == n + 1){
		if(d == r)
			P_E_i += now;
		return ;
	}
	dfs2(k + 1, i, d + 1, now * p[k]);
	if(k != i)
		dfs2(k + 1, i, d, now * (1 - p[k]));
	return ;
}

int main(){
	int Case = 1;
	while(scanf("%d%d", &n, &r) != EOF){
		if(n == 0)
			break;
		printf("Case %d:\n", Case++);

		P_E = 0;
		for(int i = 1; i <= n; i++)
			scanf("%lf", &p[i]);

		dfs1(1, 0, 1);
		for(int i = 1; i <= n; i++){
			P_E_i = 0;
			dfs2(1, i, 0, 1);
			printf("%.6lf\n", P_E_i / P_E);
		}
	}
	return 0;
}
