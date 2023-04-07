#include <iostream>
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <map>
#include <assert.h>

typedef long long ll;
const int N = 1e6 + 10;

ll siz[N << 2];

template<int SZ, int SIG = 32>
struct Suffix_Automaton{
	int link[SZ], len[SZ], last, sz;
	std::map<char, int> nxt[SZ];
	inline void init(){
		sz = 0, last = new_node();
	}

	inline int new_node(){
		assert(sz + 1 < SZ);
		int node = sz++;
		siz[node] = 1;
		link[node] = -1;
		len[node] = 0;
		return node;
	}

	inline void insert(char x){
		int p = last, cur = new_node();
		len[last = cur] = len[p] + 1;

		while(p != -1 && !nxt[p][x])
			nxt[p][x] = cur, p = link[p];

		if(p == -1){
			link[cur] = 0;
			return ;
		}

		int q = nxt[p][x];
		if(len[p] + 1 == len[q]){
			link[cur] = q;
			return ;
		}

		int newq = new_node();
		nxt[newq] = nxt[q];
		link[newq] = link[q];
		len[newq] = len[p] + 1;
		link[cur] = link[q] = newq;
		siz[newq] = 0;
		while(p != -1 && nxt[p][x] == q)
			nxt[p][x] = newq, p = link[p];
	}

	inline void build(char* s){
		for(int i = 0; s[i]; i++)
			insert(s[i]);
	}
};

char s[2 * N];
Suffix_Automaton<4 * N> SAM;
int h[4 * N], e[4 * N], ne[4 * N], idx;
ll ans = 0;

void add(int u, int v){
	e[idx] = v, ne[idx] = h[u], h[u] = idx++;
}

void dfs(int u){
	for(int i = h[u]; ~i; i = ne[i]){
		int v = e[i];
		dfs(v);
		siz[u] += siz[v];
	}
	if(siz[u] != 1)
		ans = std::max(ans, (ll)siz[u] * SAM.len[u]);
}

int main(){
	memset(h, -1, sizeof h);
	scanf("%s", s);
	SAM.init();
	SAM.build(s);

	for(int i = 1; i < SAM.sz; i++)
		add(SAM.link[i], i);

	dfs(0);
	printf("%lld\n", ans);
	return 0;
}
