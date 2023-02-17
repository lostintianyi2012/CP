#include <iostream>
#include <string.h>
#include <algorithm>
#include <vector>

using namespace std;
const int N = 1e7 + 10;
long long primes[N];
long long sum[N];
int idx;
long long phi[N];
bool st[N];
int n;

void phi_table(){
    phi[1] = 1;
    for(int i = 2; i <= n; i++){
        if(!st[i]){
            primes[++idx] = i;
            phi[i] = i-1;
        }
        for(int j = 1; primes[j] * i <= n && j <= idx; j++){
            st[primes[j] * i] = true;
            if(i % primes[j] == 0){
                phi[i * primes[j]] = phi[i] * primes[j];
                break;
            }
            phi[i * primes[j]] = phi[i] * phi[primes[j]];
        }
    }
    for(int i = 1; i <= n; i++){
        sum[i] = sum[i-1] + phi[i];
    }
}

int main(){
    scanf("%d", &n);
    phi_table();
    long long ans = 0;
    //首先若 a 与 b 互质, 那么 gcd(a*p, b*p) = p
    //所以对于每一个p, 只要知道 phi[n/p] 就可以知道有多少对互质的 a, b 可以得到答案
    for(int i = 1; i <= idx; i++){
        ans += 2 * sum[n / primes[i]];
    }
    ans -= idx;
//    for(int i = 1; i <= n; i ++)
//        printf("%d ", phi[i]);
//    puts("");
    printf("%lld\n", ans);
    return 0;
}