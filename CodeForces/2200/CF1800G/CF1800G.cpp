#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <set>
#include <unordered_map>
#include <ctime>
#include <climits>

using namespace std;
typedef unsigned long long ll;
const int N = 2e5 + 10;
const ll mod = 998244353;
int h[N], e[N << 1], ne[N << 1], idx;
ll hs[N];
int fa[N];
int size[N];
int n;

inline void add(int u, int v){
	e[idx] = v, ne[idx] = h[u], h[u] = idx++;
}

void clear(){
	memset(h, -1, (n + 2) * sizeof(int));
	memset(hs, 0, (n + 2) * sizeof(ll));
	memset(size, 0, (n + 2) * sizeof(int));
	idx = 0;
}

ll HFunction(ll x){
	return x * x * x * 1237123 + 19260817;
}

ll f(ll x){
	ll cur = HFunction(x & INT_MAX) + HFunction((x >> 31) & 1);
	return cur;
}

void dfs(int u){
	size[u] = 1;
	for(int i = h[u]; ~i; i = ne[i]){
		int v = e[i];
		if(v == fa[u])
			continue;
		fa[v] = u;
		dfs(v);
		hs[u] += f(hs[v]);
		size[u] += size[v];
	}
	hs[u] += 1;
}

bool check_mirror(int u){
	if(size[u] == 1)
		return true;

	int count = 0, midtree;
	multiset<ll> hashmap;

	for(int i = h[u]; ~i; i = ne[i]){
		int v = e[i];
		if(v == fa[u])
			continue;
		hashmap.insert(hs[v]);
	}
	set<ll> cnt2;
	for(int i = h[u]; ~i; i = ne[i]){
		int v = e[i];
		if(v == fa[u])
			continue;
		if((hashmap.count(hs[v]) & 1) && !cnt2.count(hs[v])){
			count++;
			midtree = v;
			cnt2.insert(hs[v]);
		}
	}
	if(count > 1)
		return false;
	else if(count == 1)
		return check_mirror(midtree);

	return true;
}

void solve(){
	cin >> n;
	for(int i = 1; i < n; i++){
		int u, v;
		cin >> u >> v;
		add(u, v), add(v, u);
	}
	dfs(1);
	
	bool ans = check_mirror(1);
	if(ans)
		cout << "YES\n";
	else
		cout << "NO\n";
}

int main(){
	memset(h, -1, sizeof(h));
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	int T;
	cin >> T;
	while(T--){
		clear();
		solve();
	}
	return 0;
}

