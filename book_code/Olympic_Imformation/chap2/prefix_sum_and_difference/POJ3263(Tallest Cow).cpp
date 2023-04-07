/* 
 * Author:lsty
 * Date:2023.1.27
 * Problem:POJ 3263 Tallest Cow
 * Tag:prefix sum
 */
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <map>

using namespace std;
typedef pair<int, int> PII;

const int N = 1e4 + 10;
int s[N];
int n, i, h, r;

map<PII, int> hst;

int main(){
    scanf("%d%d%d%d", &n, &i, &h, &r);
    for(int i = 1; i <= r; i++){
        int a, b;
        scanf("%d%d", &a, &b);
        if(a > b)
            swap(a, b);
        PII now = make_pair(a, b);
        if(hst[now])
            continue;
        else
            hst[now] = 1;

        s[a+1] += 1;
        s[b] -= 1;
    }

    for(int i = 1; i <= n; i++){
        s[i] += s[i-1];
    }

    for(int i = 1; i <= n; i++){
        printf("%d\n", h - s[i]);
    }

    return 0;
}