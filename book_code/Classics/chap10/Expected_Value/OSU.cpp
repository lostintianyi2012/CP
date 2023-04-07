#include <iostream>
#include <string.h>
#include <algorithm>

using namespace std;
const int N = 1e5 + 10;
double p[N], x1[N], x2[N], ans[N];
int n;

int main(){
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
		scanf("%lf", &p[i]);
	for(int i = 1; i <= n; i++){
		x1[i] = (x1[i-1] + 1) * p[i];
		x2[i] = (x2[i-1] + 2 * x1[i-1] + 1) * p[i];
		ans[i] = ans[i-1] + (3 * x2[i-1] + 3 * x1[i-1] + 1) * p[i];
	}
	printf("%.1lf\n", ans[n]);
	return 0;
}
