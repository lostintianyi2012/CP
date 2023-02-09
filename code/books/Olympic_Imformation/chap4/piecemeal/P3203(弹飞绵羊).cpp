#include <iostream>
#include <string.h>
#include <algorithm>
#include <cstdio>
#include <math.h>

const int N = 2e5 + 10;
const int M = 1e3 + 10;
int next[N];
int skip[N];
int times[N];        //times表示弹到下一个块的次数

int st[N], ed[N], pos[N];
int n, m;
int len, t;

void init(){
    len = sqrt(n);
    t = n / len;
    if(n % len) t++;
    for(int i = 1; i <= t; i++){
        st[i] = (i - 1) * len + 1;
        ed[i] = i * len;
    }
    ed[t] = n;
    for(int i = 1; i <= n; i++)
        pos[i] = (i-1) / len + 1;
    for(int i = n; i > 0; i--){
        int nxt = i + next[i];
        //跳到了下一个块
        if(pos[nxt] != pos[i]){
            times[i] = 1;
            skip[i] = nxt;
        }
        //没跳到下一个块
        else{
            times[i] = times[nxt] + 1;
            skip[i] = skip[nxt];
        }
    }
}

int query(int x){
    int ans = 0;
    while(x <= n){
        ans += times[x];
        x = skip[x];
    }
    return ans;
}

void modify(int x, int k){
    int p = pos[x];
    next[x] = k;
    for(int i = ed[p]; i >= st[p]; i--){
        int nxt = i + next[i];
        if(pos[nxt] != pos[i]){
            times[i] = 1;
            skip[i] = nxt;
        }
        else{
            times[i] = times[nxt] + 1;
            skip[i] = skip[nxt];
        }
    }
}

int main(){
    scanf("%d", &n);
    for(int i = 1; i <= n; i++){
        scanf("%d", &next[i]);
    }
    init();
    scanf("%d", &m);
    for(int i = 1; i <= m; i++){
        int op, x;
        scanf("%d%d", &op, &x);
        if(op == 1)
            printf("%d\n", query(x + 1));
        else{
            int k;
            scanf("%d", &k);
            modify(x + 1, k);
        }
    }
    return 0;
}