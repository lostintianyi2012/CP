#include <iostream>
#include <algorithm>
#include <string.h>

using namespace std;

const int N = 510;
int a[N];
int n;
double ans = 0;

int main(){
	scanf("%d", &n);
	for(int i = 1; i <= 5 * n; i++)
		scanf("%d", &a[i]);
	sort(a + 1, a + 1 + 5 * n);

	for(int i = n + 1; i <= 4 * n; i++)
		ans += a[i];

	printf("%lf\n", ans / (3 * n));
	return 0;
}
