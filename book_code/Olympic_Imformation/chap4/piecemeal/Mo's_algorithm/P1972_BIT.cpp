#include <iostream>
#include <string.h>
#include <algorithm>
#include <stdio.h>

const int N = 1e6 + 10;
int a[N], tr[N], last[N], ans[N];
int n, m;

struct que{
    int l, r, id;
}q[N];

bool cmp(que a, que b){
    return a.r == b.r ? a.l < b.l : a.r < b.r;
}

int lowbit(int x){
    return x & -x;
}

void add(int x, int k){
    for(int i = x; i <= n; i += lowbit(i)){
        tr[i] += k;
    }
}

int query(int x){
    int ans = 0;
    for(int i = x; i > 0; i -= lowbit(i)){
        ans += tr[i];
    }
    return ans;
}

int main(){
    scanf("%d", &n);
    for(int i = 1; i <= n; i++){
        scanf("%d", &a[i]);
    }
    scanf("%d", &m);
    for(int i = 1; i <= m; i++){
        scanf("%d%d", &q[i].l, &q[i].r);
        q[i].id = i;
    }
    std::sort(q + 1, q + 1 + m, cmp);

    int nxt = 1;
    for(int i = 1; i <= m; i++){
        for(int j = nxt; j <= q[i].r; j++){
            if(last[a[j]])
                add(last[a[j]], -1);
            add(j, 1);
            last[a[j]] = j;
        }
        nxt = q[i].r + 1;
        ans[q[i].id] = query(q[i].r) - query(q[i].l - 1);
    }
    for(int i = 1; i <= m; i++){
        printf("%d\n", ans[i]);
    }
    return 0;
}