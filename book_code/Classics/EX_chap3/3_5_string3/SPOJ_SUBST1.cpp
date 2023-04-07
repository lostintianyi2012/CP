#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdio>
#include <assert.h>
#include <map>

typedef long long ll;
const int N = 1e5 + 10;

template<int size, int SIG = 32>
struct suffix_automaton{
	int link[size], len[size], last, idx;
	ll F[size];
	std::map<char, int> nxt[size];
	
	inline void init(){
		memset(F, 0, sizeof F);
		idx = 0, last = new_node();
	}

	inline int new_node(){
		int node = ++idx;
		nxt[node].clear();
		link[node] = 0, len[node] = 0;
		return node;
	}

	inline void Insert(char x){
		int p = last, cur = new_node();
		len[last = cur] = len[p] + 1;

		while(p && !nxt[p].count(x))
			nxt[p][x] = cur, p = link[p];
		
		if(!p){
			link[cur] = 1;
			return ;
		}
		int q = nxt[p][x];
		if(len[q] == len[p] + 1)
			link[cur] = q;
		else{
			int nq = new_node();
			nxt[nq] = nxt[q];
			len[nq] = len[p] + 1, link[nq] = link[q];
			link[q] = link[cur] = nq;
			while(p && nxt[p][x] == q)
				nxt[p][x] = nq, p = link[p];
		}
	}

	inline void build(char* s){
		while(*s)
			Insert(*s++);
	}

	ll dp(int u){
		if(F[u])
			return F[u];
		F[u] = 1;
		if(nxt[u].size() == 0)
			return 1;
		for(std::map<char, int>::iterator it = nxt[u].begin(); it != nxt[u].end(); it++)
			F[u] += dp(it->second);
		return F[u];
	}
};

char s[N];
suffix_automaton<N * 2> SAM;

int main(){
	int T;
	scanf("%d", &T);
	while(T--){
		scanf("%s", s);
		SAM.init();
		SAM.build(s);
		printf("%lld\n", SAM.dp(1) - 1);
	}
	return 0;
}
