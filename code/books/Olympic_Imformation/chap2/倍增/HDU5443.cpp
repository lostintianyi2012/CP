/*
 * Author:lostintianyi
 * Date:2023.1.13
 * Problem:HDU5443 The Water Problem
 */
#include <bits/stdc++.h>

using namespace std;
const int N = 1e3 + 10;
int Log2[N];
long long st[11][N];
long long a[N];
int n, q;

inline void st_init(){
    for(int i = 1; i <= n; i++){
        st[0][i] = a[i];
    }

    int p = Log2[n];
    for(int k = 1; k <= p; k++){
        for(int i = 1; i + (1 << k) <= n+1; i++){
            st[k][i] = max(st[k-1][i], st[k-1][i + (1 << (k-1))]);
        }
    }
}

int main(){
    int T;
    scanf("%d", &T);

    Log2[1] = 0;
    for(int i = 2; i < N; i++){
        Log2[i] = Log2[i >> 1] + 1;
    }
    
    while(T--){
        scanf("%d", &n);
        for(int i = 1; i <= n; i++){
            scanf("%lld", &a[i]);
        }

        st_init();

        scanf("%d", &q);
        while(q--){
            int l, r;
            scanf("%d%d", &l, &r);
            int k = Log2[r - l + 1];
            printf("%lld\n", max(st[k][l], st[k][r - (1 << k) + 1]));
        }
    }
    return 0;
}