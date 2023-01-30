/* 
 * Author:lsty
 * Date:2023.1.27
 * Problem:P3406 海底高铁
 * Tag:prefix sum
 */
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int N = 1e5 + 10;
long long s[N];
long long a[N];
long long b[N];
long long c[N];
int p[N];
unsigned long long ans = 0;
int n, m;

int main(){
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= m; i++){
        scanf("%d", &p[i]);
    }
    for(int i = 1; i < n; i++){
        scanf("%lld%lld%lld", &a[i], &b[i], &c[i]);
    }
    for(int i = 2; i <= m; i++){
        int st = p[i-1], ed = p[i];
        if(st > ed)
            swap(st, ed);
        s[st] += 1;
        s[ed] -= 1;
    }

    for(int i = 1; i < n; i++){
        s[i] += s[i-1];
    }

    for(int i = 1; i < n; i++){
        ans += min(s[i] * b[i] + c[i], s[i] * a[i]);
    }
    printf("%lld\n", ans);
    return 0;
}