#include <iostream>
#include <string.h>
#include <algorithm>
#include <stdio.h>
#include <math.h>

const int N = 1e6 + 10;
const int mx = 1e3 + 5;

struct block{
    int st, ed;
    long long tag;
}blocks[mx];

int pos[N], len, t;
long long a[N];
long long b[N];
int n, m;

void init(){
    len = sqrt(n);
    t = n / len;
    if(n % len) t++;
    for(int i = 1; i <= t; i++){
        blocks[i].st = (i-1) * len + 1;
        if(i == t)
            blocks[i].ed = n;
        else
            blocks[i].ed = i * len;
        std::sort(a + blocks[i].st, a + blocks[i].ed + 1);
    }
    for(int i = 1; i <= n; i++)
        pos[i] = (i-1) / len + 1;
}

void add(int l, int r, int c){
    int p = pos[l], q = pos[r];
    if(p == q){
        for(int i = l; i <= r; i++){
            b[i] += c;
        }
        for(int i = blocks[p].st; i <= blocks[p].ed; i++)
            a[i] = b[i];
        std::sort(a + blocks[p].st, a + blocks[p].ed + 1);
    }
    else{
        for(int i = p + 1; i <= q - 1; i++)
            blocks[i].tag += c;
        for(int i = l; i <= blocks[p].ed; i++){
            b[i] += c;
        }
        for(int i = blocks[p].st; i <= blocks[p].ed; i++)
            a[i] = b[i];
        std::sort(a + blocks[p].st, a + blocks[p].ed + 1);
        for(int i = blocks[q].st; i <= r; i++)
            b[i] += c;
        for(int i = blocks[q].st; i <= blocks[q].ed; i++)
            a[i] = b[i];
        std::sort(a + blocks[q].st, a + blocks[q].ed + 1);
    }
}

int query(int l, int r, int c){
    int p = pos[l], q = pos[r];
    int ans = 0;
    if(p == q){
        int k = c - blocks[p].tag;
        for(int i = l; i <= r; i++)
            if(b[i] >= k)
                ans++;
    }
    else{
        for(int i = p + 1; i <= q - 1; i++){
            int k = c - blocks[i].tag;
            int x = std::lower_bound(a + blocks[i].st, a + blocks[i].ed + 1, k) - a;
            ans += blocks[i].ed - x + 1;
        }
        for(int i = l; i <= blocks[p].ed; i++){
            int k = c - blocks[p].tag;
            if(b[i] >= k)
                ans++;
        }
        for(int i = blocks[q].st; i <= r; i++){
            int k = c - blocks[q].tag;
            if(b[i] >= k)
                ans++;
        }
    }
    return ans;
}

int main(){
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; i++){
        scanf("%lld", &a[i]);
        b[i] = a[i];
    }

    init();

    for(int i = 1; i <= m; i++){
        char op[2];
        int l, r, c;
        scanf("%s", op);
        scanf("%d%d%d", &l, &r, &c);
        if(op[0] == 'M'){
            add(l, r, c);
        }
        else{
            printf("%d\n", query(l, r, c));
        }
    }
    return 0;
}