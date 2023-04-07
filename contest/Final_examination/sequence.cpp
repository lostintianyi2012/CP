#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;
const int N = 1010;
int a[N], ans[N];
int n;
int l, r;

int sum = 0;
void dfs2(int u, int w){
    if(u == n+1){
        sum += w;
        return ;
    }

    for(int i = u+1; i <= n+1; i++){
        dfs2(i, (w ^ a[i]));
    }
}

void dfs(int u){
    if(u == n+1){
        dfs2(0, 0);
        ans[sum]++;
        sum = 0;
        return ;
    }

    for(int i = l; i <= r; i++){
        a[u] = i;
        dfs(u + 1);
    }
}

int main(){
    freopen("sequence.in", "r", stdin);
    freopen("sequence.out", "w", stdout);
    int T;
    scanf("%d", &T);
    while(T--){
        memset(a, 0, sizeof(a));
        scanf("%d%d%d", &n, &l, &r);
        dfs(1);
        int cnt = 0;
        for(int i = 0; i <= 1010; i++){
            if(ans[i] != 0){
                cnt ++;
            }
        }
        printf("%d\n", cnt);
    }
    
    return 0;
}