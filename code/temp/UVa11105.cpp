/*
 * Copyright© 2023 lsty. All rights reserved.
 * author: lsty
 * Problem:
 * Tag:
 * Date: 2023-02-18 
 */
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
#include <math.h>
#include <time.h>

using namespace std;
const int N = 1e6 + 10;
int h_prime[N], idx;
bool is_h[N];
bool semi_h[N];
int sum[N];

void prime_sieve(){
    for(int i = 5; i < N; i += 4){
        bool flag = 1;
        for(int j = 1; j <= idx && h_prime[j] <= sqrt(i); j++){
            if(i % h_prime[j] == 0){
                flag = false;
                int k = i / h_prime[j];
                if(is_h[k]){
                    semi_h[i] = true;
                    break;
                }
            }
        }
        if(flag){
            h_prime[++idx] = i;
            is_h[i] = true;
        }
    }
}

int main() {
//    double st = clock();
    prime_sieve();
//    double ed = clock();
//    cout << (ed - st) / CLOCKS_PER_SEC << endl;
    for(int i = 1; i < N; i++){
        sum[i] = sum[i-1];
        if(semi_h[i])
            sum[i]++;
    }
    int n;
    while(scanf("%d", &n) != EOF){
        if(n == 0)
            break;
        printf("%d %d\n", n, sum[n]);
    }
    return 0;
}