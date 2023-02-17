/*
 * Copyright© 2023 lsty. All rights reserved.
 * author: lsty
 * Problem:P1516
 * Tag:Math Number Theory
 * Date: 2023-02-17 
 */
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>

using namespace std;
typedef long long ll;

void ex_gcd(ll a, ll b, ll& d, ll& x, ll& y){
    if(b == 0){ d = a, x = 1, y = 0; }
    else{
        ex_gcd(b, a % b, d, y, x);
        y -= a/b * x;
    }
}

int main() {
    ll n, m, x, y, L;
    scanf("%lld %lld %lld %lld %lld", &x, &y, &m, &n, &L);
    ll a = n - m, c = x - y;
    if(a < 0){a = -a, c = -c;}
    ll d;
    ex_gcd(a, L, d, x, y);
    if(c % d)   puts("Impossible");
    else{
        ll g = L / d;
        printf("%lld\n", (((x * (c / d)) % g + g) % g));
    }
    return 0;
}