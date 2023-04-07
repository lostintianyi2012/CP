#include <iostream>
#include <algorithm>
#include <string.h>
#include <stdio.h>

int n, D;
int main(){
	int CASE = 0;
	while(scanf("%d%d", &n, &D)){
		if(n == 0 && D == 0)
			break;
		double ans = D;
		double p, L, v;
		for(int i = 1; i <= n; i++){
			scanf("%lf %lf %lf", &p, &L, &v);
			ans += 2 * L / v;
			ans -= L;
		}
		printf("Case %d: %.3lf\n\n", ++CASE, ans);
	}
	return 0;
}
