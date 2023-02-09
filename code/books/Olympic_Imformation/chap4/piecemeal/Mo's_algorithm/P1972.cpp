#include <iostream>
#include <string.h>
#include <algorithm>
#include <cstdlib>
#include <stdio.h>
#include <math.h>

const int N = 1e6 + 10;
int n, m, Ans;
int a[N], cnt[N], ans[N];
int pos[N];

struct ques{
    int l, r, id;
}q[N];

void init(){
    int block = sqrt(n);
    for(int i = 1; i <= n; i++)
        pos[i] = (i-1) / block + 1;
}

bool cmp1(ques a, ques b){
    if(pos[a.l] != pos[b.l])
        return a.l < b.l;
    if(pos[a.l] & 1)    return a.r < b.r;
    return a.r > b.r;
}

void Add(int x){
    cnt[a[x]]++;
    if(cnt[a[x]] == 1)  Ans++;
}

void Del(int x){
    cnt[a[x]]--;
    if(cnt[a[x]] == 0)  Ans--;
}

void work(){
    int l = 1, r = 0;
    for(int i = 1; i <= m; i++){
        while(l > q[i].l)   Add(--l);
        while(r < q[i].r)   Add(++r);
        while(l < q[i].l)   Del(l++);
        while(r > q[i].r)   Del(r--);
        ans[q[i].id] = Ans;
    }
}

int main(){
    scanf("%d", &n);
    for(int i = 1; i <= n; i++){
        scanf("%d", &a[i]);
    }

    init();
    
    scanf("%d", &m);
    for(int i = 1; i <= m; i++){
        scanf("%d%d", &q[i].l, &q[i].r);
        q[i].id = i;
    }
    std::sort(q + 1, q + 1 + m, cmp1);
    work();
    for(int i = 1; i <= m; i++){
        printf("%d\n", ans[i]);
    }
    return 0;
}