#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <string.h>

using namespace std;
const int N = 2e5 + 10;
int prime[N], idx;
int phi[N];
long long n;
long long sum[N];
bool st[N];

void phi_table(){
    phi[1] = 1;
    for(int i = 2; i < N; i++){
        if(!st[i]){
            phi[i] = i-1;
            prime[++idx] = i;
        }
        for(int j = 1; j <= idx && i * prime[j] < N; j++){
            st[i * prime[j]] = true;
            if(i % prime[j] == 0){
                phi[i * prime[j]] = phi[i] * prime[j];
                break;
            }
            phi[i * prime[j]] = phi[i] * phi[prime[j]];
        }
    }
    for(int i = 1; i < N; i++){
        sum[i] = sum[i-1] + phi[i];
    }
}

int gcd(int x, int y){
    return y == 0 ? x : gcd(y, x % y);
}

int main(){
    phi_table();
    while(scanf("%lld", &n) && n){
        if(n == 1){
            puts("0/1");
            continue;
        }
        
        n--;
        int k = lower_bound(sum + 1, sum + N, n) - sum;
        n -= sum[k-1];
        int ans = 0;
        for(int i = 1; i <= k; i++){
            if(gcd(i, k) == 1){
                ans++;
                if(ans == n){
                    printf("%d/%d\n", i, k);
                    break;
                }
            }
        }
    }
    return 0;
}