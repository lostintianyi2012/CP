#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <unordered_map>
#include <queue>

using namespace std;
typedef long long ll;
const int N = 3e5 + 10, M = 1e6 + 2e5 + 10;
int fa[N], cnt[N], siz[N];
int n, m, k;
ll ans;

unordered_map <int, int> mp[N];
queue<pair<int, int>> q;
int find(int x){
	return (x == fa[x]) ? x : fa[x] = find(fa[x]);
}

void Union(int x, int y){
	x = find(x), y = find(y);
	if(x == y)	return ;
	if(siz[x] < siz[y])
		swap(x, y);
	fa[y] = x;
	siz[x] += siz[y];

	for(auto iter : mp[y]){
		//边已经被加过了, 还有一条合法括号路径
		if(mp[x].count(iter.first))
			q.push({iter.second, mp[x][iter.first]});
		//没有直接加入
		else
			mp[x][iter.first] = iter.second;
	}
	mp[y].clear();
}

int main(){
	scanf("%d%d%d", &n, &m, &k);

	for(int i = 1; i <= m; i++){
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		if(mp[v].count(w))
			q.push({u, mp[v][w]});
		else
			mp[v][w] = u;
	}
	for(int i = 1; i <= n; i++)
		fa[i] = i, siz[i] = 1;

	while(!q.empty()){
		pair<int, int> h = q.front();
		q.pop();
		Union(h.first, h.second);
	}
	for(int i = 1; i <= n; i++)
		if(i == fa[i])
			ans += 1ll * siz[i] * (siz[i] - 1) >> 1;
	printf("%lld\n", ans);
	return 0;
}
