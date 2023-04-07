#include <bits/stdc++.h>

using namespace std;
const int N = 1e5 + 10;
int tr[N], n;

inline int lowbit(int x){
	return x & (-x);
}

inline void add(int x, int k){
	for(int i = x; i <= n; i += lowbit(i)){
		tr[i] += k;
	}
}

inline int query(int x){
	int ans = 0;
	for(int i = x; i > 0; i -= lowbit(i)){
		ans += tr[i];
	}
	return ans;
}

int main(){
    while(1){
		scanf("%d", &n);
        if(n == 0){
            break;
        }

        memset(tr, 0, sizeof tr);

        int l, r;
        for(int i = 1; i <= n; i++){
            scanf("%d%d", &l, &r);
			add(l, 1), add(r + 1, -1);
        }
        
        for(int i = 1; i <= n; i++){
            printf("%d", query(i));
			if(i != n)
				printf(" ");
			else
				puts("");
        }
    }
    return 0;
}
