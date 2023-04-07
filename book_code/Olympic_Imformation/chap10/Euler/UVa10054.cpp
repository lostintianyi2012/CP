#include <iostream>
#include <string.h>
#include <stdio.h>
#include <algorithm>

using namespace std;
const int N = 55;
int g[N][N], deg[N];
int m;

void Euler(int u){
	for(int v = 1; v <= 50; v++)
		if(g[u][v]){
			g[u][v]--, g[v][u]--;
			Euler(v);
			//珠子可以反转, 保证N行第二个数等于1行第一个数
			printf("%d %d\n", v, u);
		}
}

int main(){
	int T;
	scanf("%d", &T);
	for(int CaseNum = 1; CaseNum <= T; CaseNum++){
		if(CaseNum != 1)
			printf("\n");
		printf("Case #%d\n", CaseNum);

		memset(g, 0, sizeof g);
		memset(deg, 0, sizeof deg);

		int st = 1;
		scanf("%d", &m);
		for(int i = 1; i <= m; i++){
			int u, v;
			scanf("%d%d", &u, &v);
			deg[u]++, deg[v]++;
			g[u][v]++, g[v][u]++;
			st = u;
		}

		bool flag = true;
		for(int i = 1; i <= 50; i++)
			if(deg[i] & 1){
				puts("some beads may be lost");
				flag = false;
				break;
			}
		
		if(flag){
			Euler(st);
		}	
	}
	return 0;
}
