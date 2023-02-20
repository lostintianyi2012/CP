#include <iostream>
int T;
long long n;
int main(){
    scanf("%d", &T);
    while(T--){
        scanf("%lld", &n);
        printf("%lld\n", (n + 1) / 2);
    }
    return 0;
}