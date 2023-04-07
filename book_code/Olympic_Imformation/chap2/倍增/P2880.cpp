#include <bits/stdc++.h>

using namespace std;
const int N = 5e4 + 10;
int n, m;
int a[N], maxn[22][N], minn[22][N];
int log_2[N];

void st_init(){
    log_2[0] = -1;
    for(int i = 1; i <= N; i++){
        log_2[i] = log_2[i >> 1] + 1;
    }

    for(int i = 1; i <= n; i++){
        maxn[0][i] = a[i];
        minn[0][i] = a[i];
    }
    int p = log2(n);
    for(int k = 1; k <= p; k++){
        for(int s = 1; s + (1 << k) <= n + 1; s++){
            maxn[k][s] = max(maxn[k-1][s], maxn[k-1][s + (1 << (k-1))]);
            minn[k][s] = min(minn[k-1][s], minn[k-1][s + (1 << (k-1))]);
        }
    }
}

int st_query(int l, int r){
    int k = log_2[r-l+1];
    int x = max(maxn[k][l], maxn[k][r - (1 << k) + 1]);
    int y = min(minn[k][l], minn[k][r - (1 << k) + 1]);
    return x - y;
}

int main(){
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; i++){
        scanf("%d", &a[i]);
    }
    st_init();
    for(int i = 1; i <= m; i++){
        int l, r;
        scanf("%d%d", &l, &r);
        printf("%d\n", st_query(l, r));
    }

    return 0;
}