#include <time.h>
#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <random>

std::mt19937 rnd(time(0));

int main(){
    int n = rnd() % 300 + 1, m = rnd() % 300 + 1;
    printf("%d %d\n", n, m);
    for(int i = 1; i <= n; i++){
        int k = rnd() % 1000 + 1;
        printf("%d", k);
        printf("%c", i == n ? '\n' : ' ');
    }
    for(int i = 1; i <= m; i++){
        int k = rnd() % 1000 + 1;
        printf("%d", k);
        printf("%c", i == m ? '\n' : ' ');
    }
    return 0;
}