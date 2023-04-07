#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <string.h>

using namespace std;
typedef long long ll;
const int N = 1e5 + 10;
struct node{
    int s, a;
}p[N];
long long sum[N];
long long pre[N];
long long suf[N];

bool cmp(node a, node b){
    return a.a > b.a;
}

int main(){
    int n;
    scanf("%d", &n);
    for(int i = 1; i <= n; i++)
        scanf("%d", &p[i].s);
    
    for(int i = 1; i <= n; i++)
        scanf("%d", &p[i].a);
    
    sort(p + 1, p + 1 + n, cmp);
    for(int i = 1; i <= n; i++)
        sum[i] = sum[i-1] + p[i].a;
    for(int i = 1; i <= n; i++)
        pre[i] = max(pre[i-1], (ll)p[i].s);
    for(int i = n; i >= 1; i--)
        suf[i] = max(suf[i+1], (ll)2 * p[i].s + p[i].a);

    for(int i = 1; i <= n; i++)
        printf("%lld\n", max(sum[i] + 2 * pre[i], sum[i-1] + suf[i]));
        //取前 i 个或者舍掉第 i 个换取后缀的最大
    return 0;
}