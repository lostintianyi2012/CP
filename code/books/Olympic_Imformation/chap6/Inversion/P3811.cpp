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
const int N = 3e6 + 10;
long long inv[N];
int n, p;

void inv_table(){
    inv[1] = 1;
    for(int i = 2; i <= n; i++){
        int r = p % i, k = p / i;
        inv[i] = ((long long)(p - k)*inv[r]) % p;
    }
}

int main() {
    scanf("%d%d", &n, &p);
    inv_table();
    for(int i = 1; i <= n; i++){
        printf("%lld\n", inv[i]);
    }
    return 0;
}