/*
 * Copyright© 2023 lsty. All rights reserved.
 * author: lsty
 * Problem: P5303
 * Tag: 矩阵快速幂, 斐波那契数, 组合数DP
 * Date: 2023-03-06 
 */
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>

typedef long long ll;
const ll mod = 1e9 + 7;
struct matrix{
    ll t[5][5];
    matrix(){
        memset(t, 0, sizeof t);
    }
    matrix operator * (const matrix& b) const {
        matrix c;
        for(int i = 0; i < 5; i++)
            for(int j = 0; j < 5; j++)
                for(int k = 0; k < 5; k++){
                    c.t[i][j] += (t[i][k] + b.t[k][j]) % mod;
                    c.t[i][j] %= mod;
                }
        return c;
    }
};

matrix mt_f_pow(matrix a, int k){
    matrix base;
    for(int i = 0; i < 5; i++)
        base.t[i][i] = 1;
    for(; k; k >>= 1, a = a * a){
        if(k & 1)
            base = base * a;
    }
    return base;
}

int main() {
    
    return 0;
}