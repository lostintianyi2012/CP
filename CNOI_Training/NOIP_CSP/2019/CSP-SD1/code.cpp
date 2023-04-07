/*
 * Author:lsty
 * Date:2023.2.7
 * Problem:2019 CSP-S D1 格雷码
 * Tag:推公式
 */
#include <iostream>
#include <string.h>
#include <algorithm>
#include <queue>

int main(){
    unsigned long long k;
    int n;
    std::cin >> n >> k;
    n--;
    while(n > -1){
        unsigned long long mid = ((unsigned long long)1 << n) - 1;
        if(k > mid){
            printf("1");
            unsigned long long a = 0;
            for(int i = 0; i <= n; i++)
                a += ((unsigned long long)1 << i);
            k = a - k;
        }
        else{
            printf("0");
        }
        n--;
    }
    return 0;
}