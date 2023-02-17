/*
 * Copyright© 2023 lsty. All rights reserved.
 * author: lsty
 * Problem:
 * Tag:
 * Date: 2023-02-17 
 */
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>

using namespace std;
typedef long long ll;
ll A, B, C, k;

void ex_gcd(ll a, ll b, ll& d, ll& x, ll& y){
    if(b == 0){ d = a, x = 1, y = 0;}
    else{
        ex_gcd(b, a % b, d, y, x);
        y -= a / b * x;
    }
}

int main() {
    while(1){
        scanf("%lld%lld%lld%lld", &A, &B, &C, &k);
        if(!(A || B || C || k))
            break;
        ll mod = 1ll << k;
        ll g = B - A;
        //先解 Cx + (mod)y = 1

        ll d, x, y;
        ex_gcd(C, mod, d, x, y);
        if(g % d == 0){
            ll g1 = mod / d;
            ll ans;
            ans = (((g / d * x) % g1) + g1) % g1;
            //Cx\equiv 1(mod (mod))
            printf("%lld\n", ans);      
        }
        else
            puts("FOREVER");
    }
    return 0;
}