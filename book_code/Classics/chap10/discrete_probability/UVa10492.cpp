#include <iostream>
#include <string.h>
#include <algorithm>

using namespace std;

int main(){
	double a, b, c;
	while(scanf("%lf %lf %lf", &a, &b, &c) != EOF){
		double ans = 0;
		ans = (a / (a + b) * b / (a + b - c - 1)) + (b / (a + b) * (b - 1) / (a + b - c - 1));
		printf("%.5lf\n", ans);
	}
	return 0;
}
