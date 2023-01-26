/* 
 * Author:lsty
 * Date:2023.1.26
 * Problem:POJ 1611 The Suspects
 * Tag:DSU
 */
#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;
const int N = 1e5 + 10;
int d[N], fa[N];
int n, m;

inline void init(){
	memset(d, 0, sizeof d);
	for(int i = 1; i <= n; i++){
		fa[i] = i;
	}
}

int find(int x){
	if(fa[x] != x){
		int t = fa[x];
		fa[x] = find(t);
		d[x] = (d[x] + d[t]) & 1;
	}
	return fa[x];
}

void merge(int x, int y){
	int fx = find(x), fy = find(y);
	if(fx == fy){
		return ;
	}
	else{
		fa[fx] = fy;
		d[fx] = (d[y] - d[x] + 1) & 1;
	}
}

int main(){
	int T;
	scanf("%d", &T);
	while(T--){
		scanf("%d%d", &n, &m);
		init();
		for(int i = 1; i <= m; i++){
			char op[2], x, y;
			scanf("%s%d%d", op, &x, &y);
			if(op[0] == 'D'){
				merge(x, y);
			}
			else{
				int fx = find(x), fy = find(y);

			}
		}
	}
	return 0;
}
