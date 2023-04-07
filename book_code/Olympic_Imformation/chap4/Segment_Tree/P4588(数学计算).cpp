/*
 * Author:lsty
 * Date:2023.1.28
 * Problem:P4588 数学计算
 * Tag:线段树
 */
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
typedef long long ll;
const int N = 1e5 + 10;
int pos[N];
int mod, n;
int idx;

struct node{
    int l, r;
    ll prod;
}tr[N << 2];

void pushup(int u){
    int ls = u << 1, rs = u << 1 | 1;
    tr[u].prod = tr[ls].prod * tr[rs].prod % mod;
}

void build(int u, int l, int r){
    tr[u].l = l, tr[u].r = r;
    tr[u].prod = 1;
    if(l ^ r){
        int mid = (l + r) >> 1;
        build(u << 1    ,       l, mid);
        build(u << 1 | 1, mid + 1, r  );
    }
}

ll query(int u, int l, int r){
    if(l <= tr[u].l && tr[u].r <= r){
        return tr[u].prod;
    }
    else{
        int mid = (tr[u].l + tr[u].r) >> 1;
        ll v = 1;
        if(l <= mid)    v *= query(u << 1    , l, r);
        if(r > mid)     v *= query(u << 1 | 1, l, r);
        v %= mod;
        return v;
    }
}

void modify(int u, int x, int k){
    if(tr[u].l == tr[u].r && tr[u].l == x){
        tr[u].prod = k;
        return ;
    }
    else{
        int mid = (tr[u].l + tr[u].r) >> 1;
        if(x <= mid)    modify(u << 1, x, k);
        if(x > mid)     modify(u << 1 | 1, x, k);
        pushup(u);
    }
}

int main(){
    int T;
    scanf("%d", &T);

    while (T--) {
        idx = 0;

        scanf("%d%d", &n, &mod);
        build(1, 1, n);
        for (int i = 1; i <= n; i++) {
            int op, tmp;
            scanf("%d%d", &op, &tmp);

            if (op == 1) {
                modify(1, ++idx, tmp);
                // 第 i 次操作是第 pos 次修改
                pos[i] = idx;
                printf("%lld\n", query(1, 1, idx));
            } 
            else {
                int modify_pos = pos[tmp];
                modify(1, modify_pos, 1);
                printf("%lld\n", query(1, 1, idx));
            }
        }
    }
    return 0;
}