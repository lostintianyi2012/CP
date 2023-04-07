#include <iostream>
#include <algorithm>
#include <random>
#include <string>
#include <ctime>
#include <cstdlib>

using namespace std;
typedef long long ll;
const int maxn = 50, maxm = 1010;

mt19937 rnd(time(0));

ll module(ll k, ll mod){
	return ((k % mod) + mod) % mod;
}

ll newd(ll size){
	return module(rnd(), size) + 1;
}

int main(){
	freopen("input.in", "w", stdout);
	int n = newd(maxn), m = newd(maxm);
	printf("%d %d\n", n, m);
	for(int i = 0; i < m; i++){
		back:
		int op = newd(3) - 1;
		if(op == 0){
			int l = newd(n), len = newd(n);
			printf("%d %d %d\n", op, l, min(l + len - 1, n));
		}
		else if(op == 1){
//			int l0 = newd(n), l1 = newd(n), len1 = newd(n), len2 = newd(n);
//			printf("%d %d %d %d %d\n", op, l0, min(l0 + len1 - 1, n), l1, min(l1 + len2 - 1, n));
			//只生成 0 和 2
			goto back;
		}
		else{
			int l = newd(n), len = newd(n);
			printf("%d %d %d\n", op, l, min(l + len - 1, n));
		}
	}
	return 0;
}
