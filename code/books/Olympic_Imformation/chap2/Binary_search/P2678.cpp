/*
 * Author:lostintianyi
 * Date:2023.1.11
 * Problem:P2678.cpp 跳石头
 * tag:二分答案
 */
#include <bits/stdc++.h>

using namespace std;
const int N = 50050;
int s[N];
int L, n, m;

inline bool check(int x){
    int res = 0;
    int lst = 0;
    int i = 0;
    while(i < n + 1){
        i ++;
        if(s[i] - s[lst] < x)
            res++;
        else
            lst = i;
    }
    if(res > m)
        return false;
    else
        return true;
}

int main(){
    scanf("%d%d%d", &L, &n, &m);
    for(int i = 1; i <= n; i++){
        scanf("%d", &s[i]);
    }
    s[n+1] = L;

    int l = 0, r = L + 1;
    while(l < r){
        int mid = (l + r) >> 1;
        if(check(mid))  l = mid + 1;
        else    r = mid;
    }

    printf("%d\n", l - 1);
    return 0;
}