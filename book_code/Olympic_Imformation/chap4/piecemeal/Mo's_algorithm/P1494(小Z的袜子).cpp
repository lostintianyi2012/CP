#include <iostream>
#include <string.h>
#include <algorithm>
#include <stdio.h>
#include <cstdlib>
#include <math.h>

const int N = 5e4 + 10;
int C[3][N];
int a[N];
int n, m;
int cnt[N], pos[N];
long long ansa[N], ansb[N];
long long k;

struct query{
    int l, r, id;
}q[N];

bool cmp(query a, query b){
    int pos1 = pos[a.l], pos2 = pos[b.l];
    if(pos1 != pos2)
        return pos1 < pos2;
    if(pos1 & 1)    return a.r < b.r;
    return a.r > b.r;
}

void init(){
    C[0][0] = 1;
    for(int i = 1; i <= n; i++){
        for(int j = 0; j < 3; j++){
            if(j == 0)
                C[j][i] = 1;
            else
                C[j][i] = C[j][i-1] + C[j-1][i-1];
        }
    }
}

void init2(){
    int len = sqrt(n);
    for(int i = 1; i <= n; i++){
        pos[i] = (i-1) / len + 1;
    }
}

long long gcd(long long a, long long b){
    if(b == 0)
        return a;
    else
        return gcd(b, a % b);
}

void Add(int x){
    //减去原先的方案数
    int z = a[x];
    k -= C[2][cnt[z]];
    //把这个颜色加进来
    cnt[z]++;
    //重新统计方案数
    k += C[2][cnt[z]];
}

void Del(int x){
    int z = a[x];
    k -= C[2][cnt[z]];
    cnt[z]--;
    k += C[2][cnt[z]];
}

void work(){
    int l = 1, r = 0;
    for(int i = 1; i <= m; i++){
        int ql = q[i].l, qr = q[i].r;
        while(l > ql)   Add(--l);
        while(r < qr)   Add(++r);
        while(l < ql)   Del(l++);
        while(r > qr)   Del(r--);
        long long kb = C[2][qr - ql + 1];
        long long d = gcd(k, kb);
        if(d == 0){
            ansa[q[i].id] = 0, ansb[q[i].id] = 0;
        }
        else{
            ansa[q[i].id] = k / d;
            ansb[q[i].id] = kb / d;
        }
    }
}

int main(){
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; i++){
        scanf("%d", &a[i]);
    }
    for(int i = 1; i <= m; i++){
        scanf("%d%d", &q[i].l, &q[i].r);
        q[i].id = i;
    }
    init(), init2();

    std::sort(q + 1, q + 1 + m, cmp);
    work();
    for(int i = 1; i <= m; i++){
        if(ansa[i] == 0)
            puts("0/1");
        else
            printf("%lld/%lld\n", ansa[i], ansb[i]);
    }
    return 0;
}