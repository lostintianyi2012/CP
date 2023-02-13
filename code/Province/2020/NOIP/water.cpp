#include <iostream>
#include <queue>
#include <string.h>
#include <stdio.h>
#include <algorithm>
#include <cstdlib>

const int N = 1e5 + 10;
int e[N], ne[N], h[N], idx;
int in[N], out[N];
int n, m;

inline char getc(){
    char buf[N], *p1 = buf, *p2 = buf;
    return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, N, stdin), p1 == p2) ? EOF : *p1++;
}

inline int read(){
    int s = 0, w = 1;
    char c = getc();
    while(!isdigit(c)){
        if(c == '-')
            w = -1;
        c = getc();
    }
    while(isdigit(c)){
        s = (s << 3) + (s << 1) + (c ^ 48);
        c = getc();
    }
    return s * w;
}

inline void write(__int128 x){
    if(x < 0)
        putchar('-'), x = -x;
    if(x > 9)
        write(x / 10);
    putchar(x % 10 + '0');
}

void add(int a, int b){
    e[idx] = b, ne[idx] = h[a], h[a] = idx++;
    out[a]++, in[b]++;
}

struct node{
    __int128 a;
    __int128 b;
}w[N];

__int128 gcd(__int128 a, __int128 b){
    if(b == 0)
        return a;
    return gcd(b, a%b);
}

void pull(node& to, node& from, int div){
    from.b *= div;
    to.b *= from.b;
    to.a = to.a * from.b + from.a * to.b;
    __int128 k = gcd(to.a, to.b);
    to.a /= k, to.b /= k;
}

void Topo(){
    std::queue<int> q;
    for(int i = 1; i <= n; i++){
        w[i].b = 1;
        if(in[i] == 0){
            q.push(i);
            w[i].a = 1;
        }
    }
    while(!q.empty()){
        int u = q.front();
        if(out[u] == 0)
            continue;
        for(int i = h[u]; ~i; i = ne[i]){
            int v = e[i];
            pull(w[v], w[u], out[u]);
            in[v] --;
            if(in[v] == 0)
                q.push(v);
        }
    }
}

int main(){
    memset(h, -1, sizeof h);
    n = read(), m = read();
    for(int i = 1; i <= n; i++){
        int k = read();
        for(int j = 1; j <= k; j++){
            int to = read();
            add(i, to);
        }
    }
    Topo();
    for(int i = 1; i <= n; i++){
        if(out[i] == 0){
            write(w[i].a);
            printf(" ");
            write(w[i].b);
            puts("");
        }
    }
    return 0;
}