#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdio>
#include <set>

using namespace std;
typedef pair<int, int> pii;
const int N = 5e5 + 10;
const int inf = 0x3f3f3f3f;
pii a[N];
int suffix[N];
int n;

int ABS(int x){
	return x < 0 ? -x : x;
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	int T;
	cin >> T;
	while(T--){
		cin >> n;
		for(int i = 1; i <= n; i++)
			cin >> a[i].first >> a[i].second;
		sort(a + 1, a + 1 + n);

		suffix[n + 1] = -inf;
		for(int i = n; i >= 1; i--)
			suffix[i] = max(suffix[i + 1], a[i].second);
		
		int ans = inf;
		set<int> S;
		S.insert(inf), S.insert(-inf);

		for(int i = 1; i <= n; i++){
			int x = a[i].first;
			int y = suffix[i + 1];
			ans = min(ans, ABS(x - y));
			auto it = S.lower_bound(x);
			ans = min(ans, ABS(x - max(*it, y)));
			it = S.upper_bound(x);
			it--;
			ans = min(ans, ABS(x - max(*it, y)));
			S.insert(a[i].second);
		}
		cout << ans << '\n';
	}
	return 0;
}
