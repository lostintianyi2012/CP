/*
 * Copyright© 2023 lsty. All rights reserved.
 * author: lsty
 * Problem:
 * Tag:
 * Date: 2023-02-20 
 */
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>

using namespace std;
const int N = 3e4 + 10;
int a[N];

int main() {
    int t;
    scanf("%d", &t);
    while(t--){
        int n;
        scanf("%d", &n);
        for(int i = 1; i <= n; i++)
            scanf("%d", &a[i]);
        for(int i = n; i >= 1; i--)
            a[i] = a[i] - a[i-1];
        int sum = 0;
        for(int i = 1; i <= n; i++)
            if(a[i] < 0)    sum -= a[i];
        if(a[1] >= sum)
            printf("YES\n");
        else
            printf("NO\n");
    }
    return 0;
}