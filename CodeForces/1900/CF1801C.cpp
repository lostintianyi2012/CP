#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;
const int N = 2e5 + 10;
struct album{
	vector<int> track;
	int maxn;
	bool operator < (const album& b) const {
		return maxn < b.maxn;
	}
}album[N];
int n, k;

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	int T;
	cin >> T;

	while(T--){
		cin >> n;
		for(int i = 0; i < n; i++){
			album[i].track.clear();
			album[i].maxn = 0;
			cin >> k;
			album[i].track.resize(k);
			for(int j = 0; j < k; j++){
				cin >> album[i].track[j];
				album[i].maxn = max(album[i].maxn, album[i].track[j]);
			}
		}
		sort(album, album + n);
		int premax = 0;
		int ans = 0;
		for(int i = 0; i < n; i++){
			for(auto v : album[i].track)
				if(v > premax){
					ans++;
					premax = v;
				}
		}
		cout << ans << '\n';
	}
	return 0;
}
