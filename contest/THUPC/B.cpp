#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;
int n, k;

int main(){
    cin >> n >> k;
    int ans = 0;
    for(int i = 1; i <= k; i++){
        ans += k / i;
        if(ans >= n){
            printf("%d", i);
            return 0;
        }
    }
    printf("Poor E.S.!");
    return 0;
}