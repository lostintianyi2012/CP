#include <iostream>
#include <string.h>
#include <algorithm>
#include <stdio.h>

const int N = 2e5 + 10;
long double x[N];
long double maxa = -1e9, mina = 1e9;
int n;

long double P(int a, int b, int c){
	return (x[a] + x[b] + x[c]) / (x[a] * x[b] * x[c]);
}

void work(int a, int b, int c){
	maxa = std::max(P(a, b, c), maxa);
	mina = std::min(P(a, b, c), mina);
}

bool cmp(long double a, long double b){
	return (1 / a) < (1 / b);
}

int main(){
	scanf("%d", &n);

	for(int i = 1; i <= n; i++){
		int t;
		scanf("%d", &t);
		x[i] = t;
	}

	std::sort(x + 1, x + n + 1, cmp);
	work(1, 2, 3);
	work(1, 2, n);
	work(1, n-1, n);
	work(n-2, n-1, n);
	printf("%.15Lf %.15Lf\n", mina, maxa);
	return 0;
}
