#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>

using namespace std;
typedef long long ll;
const int N = 1e5 + 5e4 + 10, M = 4e2 + 10;
ll a[N];
ll ans[M][M];
//ans[i][j]表示池子 i 在mod j下的和
int block;
int n, m;

int main(){
	scanf("%d%d", &n, &m);
	block = sqrt(n);
	for(int i = 1; i <= n; i++)
		scanf("%lld", &a[i]);
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= block; j++)
			ans[j][i % j] += a[i];

	while(m--){
		char op[2];
		int x, y;
		scanf("%s%d%d", op, &x, &y);
		if(op[0] == 'A'){
			if(x <= block)
				printf("%lld\n", ans[x][y]);
			else{
				ll res = 0;
				for(int i = y; i <= n; i += x)
					res += a[i];
				printf("%lld\n", res);
			}
		}
		else{
			for(int i = 1; i <= block; i++)
				ans[i][x % i] -= a[x];
			for(int i = 1; i <= block; i++)
				ans[i][x % i] += y;
			a[x] = y;
		}
	}
	return 0;
}
