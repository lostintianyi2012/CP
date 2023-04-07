#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <assert.h>

const int N = 2010;
int f[N][N];

template<int size, int SIG = 32>
struct suffix_automaton{
	int link[size], len[size], last, idx;
	int nxt[size][26];

	inline void init(){
		idx = 0, last = new_node();
	}

	int new_node(){
		assert(idx + 1 < size);
		link[++idx] = 0;
		len[idx] = 0;
		memset(nxt[idx], 0, sizeof nxt[idx]);
		return idx;
	}

	inline void Insert(char x){
		int p = last, cur = new_node();
		len[last = cur] = len[p] + 1;

		int c = x - 'a';
		while(p && !nxt[p][c])
			nxt[p][c] = cur, p = link[p];
		if(!p)	{link[cur] = 1; return ;}
		int q = nxt[p][c];
		if(len[p] + 1 == len[q])	{link[cur] = q; return ;}
		int nq = new_node();
		memcpy(nxt[nq], nxt[q], sizeof nxt[q]);
		link[nq] = link[q];
		len[nq] = len[p] + 1;
		link[cur] = link[q] = nq;
		while(p && nxt[p][c] == q)
			nxt[p][c] = nq, p = link[p];
	}
};

char s[N];
suffix_automaton<N * 2> SAM;

int main(){
	int T;
	scanf("%d", &T);
	while(T--){
		memset(f, 0, sizeof f);
		scanf("%s", s + 1);
		int n = strlen(s + 1);
		for(int l = 1; l <= n; l++){
			SAM.init();
			for(int r = l; r <= n; r++){
				SAM.Insert(s[r]);
				int p = SAM.last;
				f[l][r] = f[l][r - 1] + SAM.len[p] - SAM.len[SAM.link[p]];
			}
		}
		int Q;
		scanf("%d", &Q);
		while(Q--){
			int l, r;
			scanf("%d%d", &l, &r);
			printf("%d\n", f[l][r]);
		}
	}
	return 0;
}
