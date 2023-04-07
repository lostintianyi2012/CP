#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;
const int N = 1e5 + 10;
long long tr[2][N];
int l, r, k;
int n, m;

inline int lowbit(int x){
	return x & (-x);
}

inline void add(int x, int k,int d){
	for(int i = x; i <= n; i += lowbit(i)){
		tr[k][i] += d;
	}
}

inline long long query(int x, int k){
	long long ans = 0;
	for(int i = x; i > 0; i -= lowbit(i)){
		ans += tr[k][i];
	}
	return ans;
}

int main(){
	scanf("%d%d", &n, &m);
	int old = 0, a;
	for(int i = 1; i <= n; i++){
		scanf("%d", &a);
		add(i, 0, a - old);
		add(i, 1, (i-1) * (a - old));
		old = a;
	}

	for(int i = 1; i <= m; i++){
		int op, l, r;
		scanf("%d%d%d", &op, &l, &r);
		if(op == 1){
			int k;
			scanf("%d", &k);
			add(l, 0, k);
			add(r + 1, 0, -k);
			add(l, 1, k * (l-1));
			add(r + 1, 1, -k * r);
		}
		else{
			printf("%lld\n", r * query(r, 0) - query(r, 1) - ((l-1) * query(l-1, 0) - query(l-1, 1)));
		}
	}
	return 0;
}
