/*
 * Author:lsty
 * Date:2023.2.15
 * Problem:P1890 GCD区间
 * Tag:GCD
 */
#include <iostream>
#include <algorithm>
#include <stdio.h>

using namespace std;
const int N = 1e3 + 10;
int a[N];
int G[N][N];
int n, m;

int gcd(int x, int y){
    if(y == 0)
        return x;
    return gcd(y, x % y);
}

int main(){
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; i++){
        scanf("%d", &a[i]);
        G[i][i] = a[i];
    }
    for(int i = 1; i <= n; i++){
        for(int j = i + 1; j <= n; j++){
            G[i][j] = gcd(G[i][j-1], a[j]);
        }
    }
    for(int i = 1; i <= m; i++){
        int l, r;
        scanf("%d%d", &l, &r);
        printf("%d\n", G[l][r]);
    }
    return 0;
}