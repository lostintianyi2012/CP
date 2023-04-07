#include <iostream>
#include <string.h>
#include <algorithm>
#include <stdio.h>

const int N = 2010;
int tot[27];
char s[N];
double f[N], a[N], b[N], inv, p, ans = 0;

int main(){
	scanf("%s", s + 1);
	int n = strlen(s + 1);
	for(int i = 1; i <= n; i++)
		tot[s[i] - 'A']++;
	//a[i]存的是 A_{i, i+1}
	a[1] = 1, b[1] = 0.5 * n;
	//枚举第 i 行消 i + 1 行
	for(int k = 2; k < n; k++){
		double inv = 0.5 / k;
		double mul = (double)(k - 1) * inv;
		//A_{k,k-1}
		//这一行减去上一行乘 mul
		double Akk = 1 - (a[k-1] * mul);
		a[k] = (double)(k + 1) * inv / Akk;
		b[k] = (double)n * (n - 1) * inv / double(n - k);
		b[k] += (double)(k - 1) * b[k-1] * inv;
		b[k] /= Akk;
	}
	for(int i = n - 1; i >= 1; i--)
		f[i] = a[i] * f[i + 1] + b[i];
	for(int i = 0; i < 26; i++)
		ans += 1.0 * tot[i] / n * f[tot[i]];
	printf("%.1lf\n", ans);
	return 0;
}
