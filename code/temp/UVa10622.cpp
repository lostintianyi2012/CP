/*
 * Copyright© 2023 lsty. All rights reserved.
 * author: lsty
 * Problem:
 * Tag: 数论
 * Date: 2023-02-19 
 */
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
#include <math.h>

using namespace std;
long long x;

int gcd(int x, int y){
    if(y == 0)
        return x;
    else
        return gcd(y, x % y);
}

int main() {
//    freopen("in.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);
    while(scanf("%lld", &x) != EOF && x){
        bool flag = false;
        if(x < 0){
            x = -x;
            flag = true;
        }

        int k = 0;
        int ex = 0;
        for(int i = 2; i <= sqrt(x); i++){
            ex = 0;
            while(x % i == 0){
                ex++;
                x /= i;
            }
            if(ex){
                if(k == 0)   k = ex;
                else        k = gcd(ex, k);
            }
        }
        //如果把前 sqrt(x) 的素数除尽, 最后只会留下一个素数
        //不妨反证, 假设最后还剩下 p1, p2 两个素数, 他们都 > sqrt(x)
        //那么 p1p2 > x 矛盾
        //取 p1 = p2 可以发现, 最后剩下的素数指数一定是 1
        //所以如果没有除干净, 直接令 k = 1 即可
        if(x > 1)   k = 1;
        if(flag){
            while(k % 2 == 0 && k)
                k /= 2;
        }
        printf("%d\n", k);
    }
    return 0;
}