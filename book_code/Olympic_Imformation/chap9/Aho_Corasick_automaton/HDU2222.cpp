#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <string.h>
#include <queue>

using namespace std;
const int N = 1e6 + 10, M = 1e4 + 10;
char s[53];
char Temp[N];
int n;

class Aho_Corasick{
	int tr[N][26];
	int cnt[N];
	int fail[N];
	int idx;
	
	public:
	void clear(){
		memset(tr, 0, sizeof tr);
		memset(cnt, 0, sizeof cnt);
		fail[0] = 0;
		idx = 0;
	}

	void Insert(char *S){
		int u = 0;
		for(int i = 1; S[i]; i++){
			int c = S[i] - 'a';
			if(!tr[u][c])	tr[u][c] = ++idx;
			u = tr[u][c];
		}
		cnt[u]++;
	}

	void build(){
		queue<int> q;
		int u = 0;
		for(int i = 0; i < 26; i++)
			if(tr[u][i]){
				fail[tr[u][i]] = 0;
				q.push(tr[u][i]);
			}

		while(!q.empty()){
			u = q.front();
			q.pop();
			for(int i = 0; i < 26; i++){
				if(tr[u][i])
					fail[tr[u][i]] = tr[fail[u]][i], q.push(tr[u][i]);
				else
					tr[u][i] = tr[fail[u]][i];
			}
		}
	}

	int query(char *T){
		int ans = 0;
		int u = 0;
		for(int i = 1; T[i]; i++){
			u = tr[u][T[i] - 'a'];
			for(int j = u; j && cnt[j] != -1; j = fail[j]){
				if(cnt[j]){
					ans += cnt[j];
					cnt[j] = -1;
				}
			}
		}
		return ans;
	}
}Automaton;

int main(){
	int T;
	scanf("%d", &T);
	while(T--){
		scanf("%d", &n);
		Automaton.clear();

		for(int i = 1; i <= n; i++){
			scanf("%s", s + 1);
			Automaton.Insert(s);
		}
		scanf("%s", Temp + 1);
		Automaton.build();
		printf("%d\n", Automaton.query(Temp));
	}
	return 0;
}
