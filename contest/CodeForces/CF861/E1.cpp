#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
typedef long long ll;
const int N = 110, K = 32;
ll mod;
ll dp[N][K][2],ans;
int n, k;

void add(ll &x, const ll &y)
{
	x += y;
	if(x >= mod)
		x -= mod;
}

int main(){
	cin >> n >> k >> mod;

	for(int x = 0; x < k; x++){
		memset(dp,0,sizeof(dp));
		dp[0][0][0] = 1;
		for(int i = 1; i <= n; i++){
			//枚举余数
			for(int j = 0; j < k; j++){
				for(int d = 0; d < k; d++){
					if((d + d) % k == x){
						add(dp[i][(j + d) % k][1], dp[i-1][j][1]);
						add(dp[i][(j + d) % k][1], dp[i-1][j][0]);
					}
					else{
						add(dp[i][(j + d) % k][0], dp[i-1][j][0]);
						add(dp[i][(j + d) % k][1], dp[i-1][j][1]);
					}
				}
			}
		}
		add(ans, dp[n][x][1]);
	}

	cout << ans << endl;
	return 0;
}
