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
const int maxk = 1e6 + 10;
int f[maxk][2];
int n, k;

struct point{
    int x, y;
    bool operator < (point& a){
        return x < a.x;
    }
    bool operator == (point& a){
        return x == a.x;
    }
}p[maxk];

int main() {
    scanf("%d%d", &n, &k);
    for(int i = 1; i <= k; i++){
        scanf("%d%d", &p[i].x, &p[i].y);
    }
    p[0].x = 0, p[k + 1].x = 0;
    sort(p, p + k + 2);
    f[0][1] = 1;
    k = unique(p, p + k + 2) - p - 1;
    for(int i = 1; i <= k; i++){
    }
    return 0;
}