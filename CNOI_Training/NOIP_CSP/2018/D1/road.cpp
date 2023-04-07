/*
 * Author:lsty
 * Date:2023.2.6
 * Problem:NOIP 2018 D1T1 铺设道路
 * Tag:模拟
 */
#include <iostream>
#include <cstdio>

int last, a;
long long ans = 0;
int main(){
    int n;
    scanf("%d", &n);
    for(int i = 1; i <= n; i++){
        scanf("%d", &a);
        ans += std::max(0, a - last);
        last = a;
    }
    printf("%lld\n", ans);
    return 0;
}