#include <iostream>
#include <string.h>
#include <algorithm>
#include <stdio.h>

using namespace std;
const int N = 1e3 + 10;
long long f[N][N];
struct node{
    int s, a;
}p[N];
int n;

int main(){
    scanf("%d", &n);
    for(int i = 1; i <= n; i++){
        scanf("%d", &p[i].s);
    }
    for(int i = 1; i <= n; i++){
        scanf("%d", &p[i].a);
    }

    for(int i = 1; i <= n; i++){
        f[i][0] = 2 * p[i].s;
    }
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= i; j++){
            for(int k = j-1; k < i; k++){
                f[i][j] = max(f[i][j], max(f[i-1][j], f[k][j-1] + p[i].a + 2 * (p[i].s - p[k].s)));
            }
        }
    }
    for(int i = 1; i <= n; i++){
        printf("%lld\n", f[n][i]);
    }
    return 0;
}