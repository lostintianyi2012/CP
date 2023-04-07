/*
 * Author:lsty
 * Date:2023.1.27
 * Problem:P1052 过河
 * Tag:Discretization
 */
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;
const int N = 1e5 + 10;
int a[105];
bool vis[N];
int f[N];
int stone[105];
int l, s, t, m;

int main(){
    scanf("%d", &l);
    scanf("%d%d%d", &s, &t, &m);
    int maxd = s * t;
    for(int i = 1; i <= m; i++){
        scanf("%d", &stone[i]);
    }
    
    if(s == t){
        int ans = 0;
        for(int i = 1; i <= m; i++){
            if(!(stone[i] % s)){
                ans++;
            }
        }
        printf("%d\n", ans);
        return 0;
    }

    sort(stone + 1, stone + 1 + m);
    int last = 0;

    for(int i = 1; i <= m; i++){
        int d = stone[i] - stone[i-1];
        d = min(d, maxd);
        a[i] = a[i-1] + d;
        vis[a[i]] = 1;
    }

    l = a[m] + maxd;
    memset(f, 0x3f, sizeof f);
    f[0] = 0;
    for(int i = 1; i <= l; i++){
        int d = vis[i];
        for(int j = s; j <= t; j++){
            if(i - j >= 0)
                f[i] = min(f[i], f[i - j] + d);
        }
    }
    int ans = 0x3f3f3f3f;
    for(int i = a[m]; i <= l; i++)
        ans = min(ans, f[i]);

    printf("%d\n", ans);

    return 0;
}