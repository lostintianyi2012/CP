#include <iostream>
#include <algorithm>
#include <string.h>
#include <stdio.h>

using namespace std;
const int N = 110, M = 10010;
int fa[N];
int n, m;

struct edge{
    int u, v, w;
}e[M];

bool cmp(edge a, edge b){
    return a.w > b.w;
}

int find(int x){
    return fa[x] == x ? x : fa[x] = find(fa[x]);
}

int main(){
    int CASENUM = 0;
    while(1){
        scanf("%d%d", &n, &m);
        if(!n && !m)
            break;
        for(int i = 1; i <= n; i++)
            fa[i] = i;
        for(int i = 1; i <= m; i++){
            scanf("%d%d%d", &e[i].u, &e[i].v, &e[i].w);
        }
        sort(e + 1, e + 1 + m, cmp);
        int s, t, num;
        scanf("%d%d%d", &s, &t, &num);

        int held = 0;
        for(int i = 1; i <= m; i++){
            int fu = find(e[i].u), fv = find(e[i].v);
            if(fu == fv)
                continue;
            else
                fa[fu] = fv;
            if(find(s) == find(t)){
                held = e[i].w;
                break;
            }
        }
        held--;
        int ans = num / held;
        if(num % held)  ans++;
        printf("Scenario #%d\n", ++CASENUM);
        printf("Minimum Number of Trips = %d\n", ans);
        printf("\n");
    }
    return 0;
}