#include <iostream>
#include <string.h>
#include <stdio.h>

using namespace std;
const int N = 1e5 + 10;
bool st[N];
int primes[N], idx;
long long sum[N];
int phi[N];
int n;

void phi_table(){
    phi[1] = 1;
    for(int i = 2; i <= n; i++){
        if(!st[i]){
            primes[++idx] = i;
            phi[i] = i - 1;
        }
        for(int j = 1; j <= idx && i * primes[j] <= n; j++){
            st[i * primes[j]] = true;
            if(i % primes[j] == 0){
                phi[i * primes[j]] = phi[i] * primes[j];
                break;
            }
            phi[i * primes[j]] = phi[i] * phi[primes[j]];
        }
    }
    for(int i = 1; i <= n; i++)
        sum[i] = sum[i-1] + phi[i];
}

int main(){
    scanf("%d", &n);
    phi_table();
    long long ans = 0;
    for(int i = 1; i <= n; i++){
        ans += ((long long)2 * sum[n / i] - 1) * (long long)i;
    }
    printf("%lld\n", ans);
    return 0;
}