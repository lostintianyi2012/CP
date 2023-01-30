/* 
 * Author:lsty
 * Date:2023.1.27
 * Problem:P2280 激光炸弹
 * Tag:prefix sum
 */
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;
const int N = 5e3 + 10;
int s[N][N];
int n, m;
int l, k;

int main(){
    int maxx = -1, maxy = -1;
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; i++){
        int x, y, v;
        scanf("%d%d%d", &x, &y, &v);
        x++, y++;
        s[x][y] += v;
        maxx = max(maxx, x);
        maxy = max(maxy, y);
    }

    int ans = 0;

    for(int i = 1; i <= maxx; i++){
        for(int j = 1; j <= maxy; j++){
            s[i][j] += s[i-1][j] + s[i][j-1] - s[i-1][j-1];
        }
    }

    m--;
    for(int i = min(m, maxx); i <= maxx; i++){
        for(int j = min(m, maxy); j <= maxy; j++){
            l = max(i - m - 1, 0);
            k = max(j - m - 1, 0);
            ans = max(ans, s[i][j] - s[i][k] - s[l][j] + s[l][k]);
        }
    }

    printf("%lld\n", ans);
    return 0;
}