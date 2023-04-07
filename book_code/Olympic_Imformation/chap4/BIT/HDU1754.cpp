#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>

using namespace std;
typedef long long ll;
const int N = 2e5 + 10;
ll a[N], tr[N];
int n, m;

int lowbit(int x){
	return x & -x;
}

void update(int x, ll k){
	while(x <= n){
		tr[x] = k;
		for(int i = 1; i < lowbit(x); i <<= 1)
			tr[x] = max(tr[x], tr[x - i]);
		x += lowbit(x);
	}
}

ll query(int l, int r){
	ll ans = 0;
	while(l <= r){
		ans = max(ans, a[r]);
		r--;
		while(r - l >= lowbit(r)){
			ans = max(ans, tr[r]);
			r -= lowbit(r);
		}
	}
	return ans;
}

int main(){
	while(scanf("%d%d", &n, &m) != EOF){
		for(int i = 1; i <= n; i++)
			scanf("%lld", &a[i]), update(i, a[i]);
		char op[2];
		for(int i = 1; i <= m; i++){
			scanf("%s", op);
			if(op[0] == 'Q'){
				int l, r;
				scanf("%d%d", &l, &r);
				printf("%lld\n", query(l, r));
			}
			else{
				int x;
				ll k;
				scanf("%d%lld", &x, &k);
				a[x] = k;
				update(x, k);
			}
		}
		memset(tr, 0, sizeof tr);
		memset(a, 0, sizeof a);
	}
	return 0;
}
