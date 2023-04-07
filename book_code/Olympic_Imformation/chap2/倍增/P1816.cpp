#include <iostream>
#include <cstdio>

using namespace std;
const int N = 1e5 + 10;
int st[22][N];
int lg[N];
int n, m;

int main(){
    scanf("%d%d", &n, &m);
    for(int i = 2; i <= n; i++){
        lg[i] = lg[i >> 1] + 1;
    }

    for(int i = 1; i <= n; i++){
        scanf("%d", &st[0][i]);
    }

    for(int k = 1; k <= lg[n]; k++){
        for(int i = 1; i + (1 << k) - 1 <= n; i++){
            st[k][i] = min(st[k-1][i], st[k-1][i + (1 << (k-1))]);
        }
    }

    for(int i = 1; i <= m; i++){
        int l, r, len;
        int k;
        scanf("%d%d", &l, &r);
        len = r - l + 1;
        k = lg[len];
        printf("%d", min(st[k][l], st[k][r - (1 << k) + 1]));
        if(i == m)
            printf("\n");
        else
            printf(" ");
    }
    return 0;
}