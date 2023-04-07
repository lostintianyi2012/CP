#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdio>
#include <map>
#include <assert.h>

const int N = 1e4 + 10;
template<int maxn, int SIG = 32>
struct suffix_automaton{
	int link[maxn], len[maxn], last, idx;
	std::map<char, int> nxt[maxn];

	void init(){
		idx = 0, last = new_node();
	}

	int new_node(){
		assert(idx + 1 < maxn);
		int node = idx++;
		nxt[node].clear(), link[node] = -1, len[node] = 0;
		return node;
	}

	void Insert(char x){
		int p = last, cur = new_node();
		len[last = cur] = len[p] + 1;

		while(p != -1 && !nxt[p].count(x))
			nxt[p][x] = cur, p = link[p];

		if(p == -1){
			link[cur] = 0;
			return ;
		}
		int q = nxt[p][x];
		if(len[q] == len[p] + 1)
			link[cur] = q;
		else{
			int newq = new_node();
			nxt[newq] = nxt[q];
			len[newq] = len[p] + 1, link[newq] = link[q];
			link[cur] = link[q] = newq;
			while(p != -1 && nxt[p][x] == q)
				nxt[p][x] = newq, p = link[p];
		}
	}

	void build(char *s){
		for(int i = 0; s[i]; i++)
			Insert(s[i]);
	}
};

char s[N];
suffix_automaton<4 * N> SAM;

int main(){
	int T;
	scanf("%d", &T);
	while(T--){
		scanf("%s", s);
		SAM.init();
		SAM.build(s), SAM.build(s);
		int p = 0, n = strlen(s);
		for(int i = 0; i < n; i++)
			p = SAM.nxt[p].begin()->second;
		printf("%d\n", SAM.len[p] - n + 1);
	}
	return 0;
}
