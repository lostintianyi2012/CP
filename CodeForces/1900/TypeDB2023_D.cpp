#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
typedef long long ll;
const int N = 2e5 + 10;
int h[N], e[N], ne[N], idx;
int v[N], s[N], a[N];
int n;

void clear()
{
	for(int i = 1; i <= n + 1; i++)
		v[i] = 0, s[i] = 0, h[i] = 0;
}

void add(int u, int v)
{
	e[++idx] = v, ne[idx] = h[u], h[u] = idx;
}

void dfs(int u)
{
	v[u] = s[u] = 1;
	for(int i = h[u]; i; i = ne[i]){
		dfs(e[i]);
		s[u] += s[e[i]];
	}
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);

	int T;
	cin >> T;
	while(T--){
		clear();
		cin >> n;
		for(int i = 1; i <= n; i++) {
			cin >> a[i];
			int v = min(n + 1, i + a[i]);
			if(v <= 0)	v = n + 1;
			a[i] = v;
			add(a[i], i);
		}
		ll ans = 0;
		dfs(n + 1);

		if(v[1] == 1) {
			ans = 1ll * n * (2 * n + 1);
			for(int j = 1; j != n + 1; j = a[j])
				ans -= s[j] + (n - s[n + 1] + 1);
		} else {
			for(int j = 1; v[j] != 2; j = a[j]){
				v[j] = 2;
				ans += (n + s[n + 1]);
			}
		}
		cout << ans << '\n';
	}
	return 0;
}
