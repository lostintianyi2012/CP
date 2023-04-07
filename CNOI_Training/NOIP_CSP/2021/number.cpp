/*
 * Author:lsty
 * Date:2023.2.16
 * Problem:NOIP 2021 T1 报数
 * Tag:
 */
#include <iostream>
#include <string.h>
#include <algorithm>
#include <bitset>
#include <time.h>

using namespace std;
const int N = 1e7 + 1000;
bitset<N + 10> st;
int nxt[N];
int ans[N], idx;

bool check(int x){
    while(x){
        if(x % 10 == 7)
            return true;
        x /= 10;
    }
    return false;
}

void table_init(){
    for(int i = 1; i <= N; i++){
        if(st[i])
            continue;
        if(check(i)){
            for(int j = 1; i * j <= N; j++)
                st[i * j] = 1;
        }
    }
    for(int i = 1; i <= N; i++)
        if(!st[i])
            ans[++idx] = i;
}

int main(){
    freopen("number.in", "r", stdin);
    freopen("number.out", "w", stdout);
    table_init();
    int t;
    scanf("%d", &t);
    while(t--){
        int k;
        scanf("%d", &k);
        int x = lower_bound(ans + 1, ans + 1 + idx, k) - ans;
        if(ans[x] != k)
            puts("-1");
        else
            printf("%d\n", ans[x + 1]);
    }
    return 0;
}