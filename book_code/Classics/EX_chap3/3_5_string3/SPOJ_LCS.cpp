#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <map>

const int N = 3e5 + 10;
template<int size, int SIG = 32>
struct suffix_automaton{
	int link[size], len[size], last, idx;
	std::map<char, int> nxt[size];
	void init(){
		idx = 0, last = new_node();
	}

	int new_node(){
		nxt[++idx].clear();
		link[idx] = 0, len[idx] = 0;
		return idx;
	}

	void Insert(char x){
		int p = last, cur = new_node();
		len[last = cur] = len[p] + 1;
		
		while(p && !nxt[p].count(x))
			nxt[p][x] = cur, p = link[p];
		if(!p)	{link[cur] = 1; return ;}
		int q = nxt[p][x];
		if(len[p] + 1 == len[q])	{link[cur] = q; return ;}
		int nq = new_node();
		nxt[nq] = nxt[q];
		link[nq] = link[q], len[nq] = len[p] + 1;
		link[q] = link[cur] = nq;
		while(p && nxt[p][x] == q)
			nxt[p][x] = nq, p = link[p];
	}

	void build(char *s){
		while(*s)
			Insert(*s++);
	}
};

char A[N], B[N];
suffix_automaton<N * 2> SAM;
int ans = 0;

int main(){
	scanf("%s", A);
	SAM.init();
	SAM.build(A);

	scanf("%s", B);
	int p = 1, l = 0;
	int n = strlen(B);

	for(int i = 0; i < n; i++){
		if(SAM.nxt[p].count(B[i]))
			p = SAM.nxt[p][B[i]], l++;
		else{
			while(p && !SAM.nxt[p].count(B[i]))
					p = SAM.link[p];
			if(p)
				l = SAM.len[p] + 1, p = SAM.nxt[p][B[i]];
			else
				p = 1, l = 0;
		}
		ans = std::max(ans, l);
	}
	printf("%d\n", ans);
	return 0;
}
