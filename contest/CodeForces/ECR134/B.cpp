#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	int T;
	cin >> T;
	while(T--){
		int n, m, sx, sy, d;
		cin >> n >> m >> sx >> sy >> d;
		int ans = n + m - 2;
		if((sx + d >= n && sx - d <= 1) || (sy + d >= m && sy - d <= 1))
			ans = -1;
		if((sx + d >= n && sy + d >= m) || (sx - d <= 1 && sy - d <= 1))
			ans = -1;
		cout << ans << '\n';
	}
	return 0;
}
