/* 
 * Author:lsty
 * Date:2023.1.27
 * Problem:P3397 地毯
 * Tag:prefix sum
 */
#include <iostream>
#include <cstdio>

using namespace std;
const int N = 1e3 + 10;
int a[N][N];
int s[N][N];
int n, m;

int main(){
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= m; i++){
        int x1, y1, x2, y2;
        scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
        a[x1][y1] += 1;
        a[x1][y2+1] -= 1;
        a[x2+1][y1] -= 1;
        a[x2+1][y2+1] += 1;
    }

    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= n; j++){
            s[i][j] = s[i-1][j] + s[i][j-1] - s[i-1][j-1] + a[i][j];
        }
    }
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= n; j++){
            printf("%d ", s[i][j]);
        }
        puts("");
    }
    return 0;
}