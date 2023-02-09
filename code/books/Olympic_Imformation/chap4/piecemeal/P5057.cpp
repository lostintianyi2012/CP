#include <iostream>
#include <string.h>
#include <algorithm>
#include <cstdlib>
#include <math.h>

const int N = 1e5 + 10;
const int M = 1e3 + 10;
int n, m;
int a[N];
struct block{
    int st, ed;
    int tag;
}blocks[M];
int pos[N];

void init(){
    int len = sqrt(n);
    int t = n / len;
    if(n % len) t++;
    for(int i = 1; i <= t; i++){
        blocks[i].st = (i-1) * len + 1;
        blocks[i].ed = i * len;
    }
    for(int i = 1; i <= n; i++){
        pos[i] = (i - 1) / len + 1;
    }
}

void modify(int l, int r){
    int p = pos[l], q = pos[r];
    if(p == q){
        for(int i = l; i <= r; i++)
            a[i] ^= 1;
    }
    else{
        for(int i = p + 1; i <= q - 1; i++)
            blocks[i].tag ^= 1;
        for(int i = l; i <= blocks[p].ed; i++)
            a[i] ^= 1;
        for(int i = blocks[q].st; i <= r; i++)
            a[i] ^= 1;
    }
}

int query(int k){
    int p = pos[k];
    return a[k] ^ blocks[p].tag;
}

int main(){
    scanf("%d", &n);
    scanf("%d", &m);
    init();
    for(int i = 1; i <= m; i++){
        int op, l, r;
        scanf("%d", &op);
        if(op == 1){
            scanf("%d%d", &l, &r);
            modify(l, r);
        }
        else{
            int k;
            scanf("%d", &k);
            printf("%d\n", query(k));
        }
    }
    return 0;
}