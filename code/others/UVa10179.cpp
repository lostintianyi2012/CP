#include <iostream>
#include <string.h>
#include <algorithm>

using namespace std;
long long n;
long long phi(long long n){
    long long ans = n;
    for(long long i = 2; i * i <= n; i++){
        if(n % i == 0){
            ans = ans / i * (i-1);
            while(n % i == 0)   n /= i;
        }
    }
    if(n > 1)   ans = ans / n * (n-1);
    return ans;
}

int main(){
    while(scanf("%lld", &n) && n){
        printf("%lld\n", phi(n));
    }
    return 0;
}