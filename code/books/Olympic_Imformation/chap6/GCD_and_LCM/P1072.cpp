#include <iostream>
#include <string.h>
#include <algorithm>
#include <stdio.h>
#include <time.h>
#include <bitset>

using namespace std;
const int N = 1e8 + 10;
int a0, a1, b0, b1;
long long ans = 0;

int gcd(int a, int b){
    return b == 0 ? a : gcd(b, a % b);
}

int main(){
    int T;
    scanf("%d", &T);
    while(T--) {
        scanf("%d%d%d%d", &a0, &a1, &b0, &b1);
        ans = 0;
        int p = a0 / a1, q = b1 / b0;
        for(int x = 1; x * x <= b1; x++){
            if(b1 % x == 0 && x % a1 == 0)
                if(gcd(x / a1, p) == 1 && gcd(b1 / x, q) == 1)
                    ans++;
            int y = b1 / x;
            if(y == x)  continue;
            if(b1 % y == 0 && y % a1 == 0)
                if(gcd(y / a1, p) == 1 && gcd(b1 / y, q) == 1)
                    ans++;
        }
        printf("%lld\n", ans);
    }
    return 0;
}