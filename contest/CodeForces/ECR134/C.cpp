#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <set>

using namespace std;
const int N = 2e5 + 10;
int a[N], b[N];
int ansmin[N], ansmax[N];

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	int T;
	cin >> T;
	while(T--){
		int n;
		cin >> n;
		for(int i = 1; i <= n; i++)
			cin >> a[i];
		for(int i = 1; i <= n; i++)
			cin >> b[i];

		for(int i = 1; i <= n; i++){
			int k = lower_bound(b + 1, b + 1 + n, a[i]) - b;
			ansmin[i] = b[k] - a[i];
		}
		int lst = n + 1;
		for(int i = n; i >= 1; i--){
			int k = lower_bound(b + 1, b + 1 + n, a[i]) - b;
			if(k == i){
				for(int j = i; j < lst; j++)
					ansmax[j] = b[lst - 1] - a[j];
				lst = k;
			}
		}
		for(int i = 1; i <= n; i++)
			cout << ansmin[i] << ' ';
		cout << '\n';
		for(int i = 1; i <= n; i++)
			cout << ansmax[i] << ' ';
		cout << '\n';
	}
	return 0;
}
