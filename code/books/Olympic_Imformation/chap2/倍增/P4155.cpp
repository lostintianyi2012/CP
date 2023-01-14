#include <bits/stdc++.h>

using namespace std;
const int N = 4e5 + 10;
int n, m;
struct node{
    int id, l, r;
    bool operator < (const node b) const {
        return  l < b.l;
    }
}w[N << 1];
int go[N][20];
int n2;

void init(){
    int nxt = 1;
    for(int i = 1; i <= n2; i++){
        while(nxt <= n2 && w[nxt].l <= w[i].r){
            nxt++;
        }
        go[i][0] = nxt - 1;
    }
    for(int i = 1; (1 << i) <= n; ++i){
        for(int s = 1; s <= n2; s++){
            go[s][i] = go[go[s][i-1]][i-1];
        }
    }
}

int res[N];

void calc(int x){
    int len = w[x].l + m;
    int cur = x, ans = 1;

    for(int i = log2(n); i >= 0; i--){
        int pos = go[cur][i];
        if(pos && w[pos].r < len){
            ans += 1 << i;
            cur = pos;
        }
    }
    res[w[x].id] = ans + 1;
}

int main(){
    scanf("%d%d", &n, &m);

    for(int i = 1; i <= n; i ++){
        w[i].id = i;
        scanf("%d%d", &w[i].l, &w[i].r);
        if(w[i].r < w[i].l)     w[i].r += m;
    }

    sort(w + 1, w + 1 + n);
    n2 = n;

    for(int i = 1; i <= n; i++){
        n2++;
        w[n2] = w[i];
        w[n2].l += m;
        w[n2].r += m;
    }

    init();
    for(int i = 1; i <= n; i++)     calc(i);
    for(int i = 1; i <= n; i++)     printf("%d ", res[i]);
    return 0;
}