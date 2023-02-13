#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <string.h>

const int N = 1e6 + 10;
int fa[N], n, m;
int a[N], b[N], idx;

struct line{
    int s, t;
    int len;
}l[N];

bool cmp(line& a, line& b){
    return a.len < b.len;
}

int id(int x, int y){
    return (x - 1) * m + y;
}

int main(){
    scanf("%d%d", &n, &m);
    a[0] = 0x3f3f3f3f, b[0] = 0x3f3f3f3f;
    for(int i = 1; i <= n; i++)
        scanf("%d", &a[i]);
    for(int i = 1; i <= m; i++)
        scanf("%d", &b[i]);

    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= m; j++){
            int up = id(i-1, j);
            
        }
    }
    return 0;
}