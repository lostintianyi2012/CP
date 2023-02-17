#include <cstdio>
#include <iostream>
#include <string.h>
using namespace std;

int A[50005];
int s[50005];
int vis[50005];

int main()
{
    int n;
    memset(s, 0, sizeof(s));
    memset(vis, 0, sizeof(vis));

    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &A[i]);
        s[i] = (s[i - 1] % n) + (A[i] % n);
        s[i] %= n;
    }

    for (int i = 1; i <= n; i++)
        if (s[i] == 0) {
            printf("%d\n", i);
            for (int j = 1; j <= i; j++)
                printf("%d\n", A[j]);
            return 0;
        }

    for (int i = 1; i <= n; i++) {
        if (vis[s[i]] != 0) { 
            printf("%d\n", i - vis[s[i]]);
            for (int j = vis[s[i]] + 1; j <= i; j++)
                printf("%d\n", A[j]);
            break;
        }
        vis[s[i]] = i;
    }
    return 0;
}